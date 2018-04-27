#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "SPI.h"

#define SOCKET_MAXDATASIZE	4800
#define SOCKET_PORT			7521
#define SOCKET_BACKLOG		10

#define PACKET_SIZE			164
#define PACKET_SIZE_UINT16	(PACKET_SIZE/2)
#define PACKETS_PER_FRAME	60
#define FRAME_SIZE_UINT16	(PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

int main(int argc, char *argv[]){

	//Socket stuffs
	int socket_sockfd;
	int socket_newsockfd;
	int socket_port;
	int socket_data;
	int socket_binding;

	//Socket buffers; max. data length which can be sent at once is around 11500 bytes, so 1200 will work just fine
	uint8_t socket_buffer_a[SOCKET_MAXDATASIZE/4];
	uint8_t socket_buffer_b[SOCKET_MAXDATASIZE/4];
	uint8_t socket_buffer_c[SOCKET_MAXDATASIZE/4];
	uint8_t socket_buffer_d[SOCKET_MAXDATASIZE/4];

	uint8_t socket_buffer_loseData[6];

	uint16_t socket_buffer_sendTemp[6]; //Buffer width temperature in *C

	socklen_t socket_clientlength;
	struct sockaddr_in server_address, client_address;

	//Flir Lepton Stuffs

	uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
	uint16_t *frameBuffer;
	int transformed_buffer[80][60];

	//Temperatures
	int lepton_min_temp;
	int lepton_max_temp;
	int lepton_center_temp;

	printf("\n\n");

	//If no arguments are introduced set the "default" host port.
	if(argc < 3){
		printf("USAGE: port\nInitializing connection with default parameters\nPORT: 7521\n\n");
		socket_port = SOCKET_PORT;
	}
	else{
		//Convert to int the arg[2] (the port)
		socket_port = atoi(argv[2]);
	}

	//Create socket
	socket_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//check if the socket can be opened
	if(socket_sockfd < 0){
		printf("ERROR: The socket cannot be opened\nExiting...\n\n");
		exit(1);
	}

	//Set all arguments to "0"
	bzero((char *) &server_address, sizeof(server_address));

	//Set the arguments for server
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(socket_port);

	memset(&(server_address.sin_zero), '\0', 8);

	//Create and the bind
	socket_binding = bind(socket_sockfd, (struct sockaddr *) &server_address, sizeof(server_address));
	if(socket_binding < 0){
		printf("ERROR: Cannot bind the socket\nExiting...\n\n");
		exit(1);
	}

	//Init the connection and accept the client
	listen(socket_sockfd, SOCKET_BACKLOG);

	//Accept the client
	socket_clientlength = sizeof(client_address);
	socket_newsockfd = accept(socket_sockfd, (struct sockaddr *) &client_address, &socket_clientlength);
	if(socket_newsockfd < 0){
		printf("ERROR: Client not accepted\nExiting...\n\n");
		exit(1);
	}

	SpiOpenPort(1);
	while(1){
		//Here is the sensor driver from sparkfun
		int resets = 0;
		for(int j=0; j<PACKETS_PER_FRAME; j++){
		read(spi_cs1_fd, result+sizeof(uint8_t)*PACKET_SIZE*j, sizeof(uint8_t)*PACKET_SIZE);
			int packetNumber = result[j*PACKET_SIZE+1];
			if(packetNumber != j){
				j = -1;
				resets += 1;
				usleep(1000);
				if(resets == 750){
					SpiClosePort(1);
					usleep(750000);
					SpiOpenPort(1);
				}
			}
		}

		frameBuffer = (uint16_t *)result;
		int row, column;
		uint16_t value;
		uint16_t minValue = 65535;
		uint16_t maxValue = 0;
		uint16_t centerValue = 0;

		for(int i=0; i<FRAME_SIZE_UINT16; i++){
			if(i%PACKET_SIZE_UINT16 < 2){
				continue;
			}

			//Flip the MSB and LSB at the last second
			int temp = result[i*2];
			result[i*2] = result[i*2+1];
			result[i*2+1] = temp;

			value = frameBuffer[i];
			if(value > maxValue){
				maxValue = value;
			}

			if(value < minValue){
				minValue = value;
			}

			column = i%PACKET_SIZE_UINT16 - 2;
			row = i / PACKET_SIZE_UINT16;

			//If reaches the center od the screen collect the value of pixel to calculate the temp
			if(column == 40 && row == 30){
				centerValue = value;
			}
		}

		float diff = maxValue - minValue;
		float scale = 255/diff;

		int z = 0;
		for(int i=0; i<FRAME_SIZE_UINT16; i++){
			if(i%PACKET_SIZE_UINT16 < 2){
				continue;
			}

			value = (frameBuffer[i] - minValue) * scale;
			column = (i%PACKET_SIZE_UINT16) - 2;
			row = i / PACKET_SIZE_UINT16;

			//We fill the "transformed buffer" with a color value between 0 and 255
			//The framebuffer contain a 16bit word and we need to "transform" it in 8bit word
			//The easiest way was to create a matrix, and of course was possible fill directly the socket buffers, but is better to have another buffer before to avoid
			transformed_buffer[column][row] = value;
		}

		//----------------------------END OF SENSOR DRIVER------------------------------//
		int socket_buffer_stage = 0;
 



		while(socket_buffer_stage < 5){
			int socket_buffer_cnt = 0;
			switch(socket_buffer_stage){
			case 0:
				//---------------------------------START OF BUFFER A----------------------------------//
				socket_buffer_cnt = 0;

				//Fill the buffer A with first 15 rows
				for(int i=0; i<15; i++){
					for(int j=0; j<80; j++){
						if(socket_buffer_cnt >= 1200){
							socket_buffer_cnt = 0;
						}

						socket_buffer_a[socket_buffer_cnt] = (uint8_t)transformed_buffer[j][i];
						
						if(socket_buffer_cnt < 1200){
							socket_buffer_cnt++;
						}
					}
				}
			//Sent buffer A
				socket_data = send(socket_newsockfd, socket_buffer_a, (SOCKET_MAXDATASIZE/4), 0);
				
				if(socket_data < 0){
				
					printf("ERROR: Data not sent   %d\nExiting...\n\n", socket_data);
					exit(1);
				}
				//---------------------------------END OF BUFFER A------------------------------------//
				break;

			case 1:
				//--------------------------------START OF BUFFER B-----------------------------------//
				socket_buffer_cnt = 0;
				
				//Fill the buffer B with rows 16-30
				for(int i=15; i<30; i++){
					for(int j=0; j<80; j++){
						if(socket_buffer_cnt >= 1200){
							socket_buffer_cnt = 0;
						}

						socket_buffer_b[socket_buffer_cnt] = (uint8_t)transformed_buffer[j][i];

						if(socket_buffer_cnt < 1200){
							socket_buffer_cnt++;
						}
					}
				}
				//Send buffer B
				socket_data = send(socket_newsockfd, socket_buffer_b, (SOCKET_MAXDATASIZE/4), 0);
				
				if(socket_data < 0){
					printf("ERROR: Data not sent\nExiting...\n\n");
					exit(1);
				}
				//---------------------------------END OF BUFFER B------------------------------------//
				break;

			case 2:
				//--------------------------------START OF BUFFER C-----------------------------------//
				socket_buffer_cnt = 0;

				//Fill the buffer C with row 31-45
				for(int i=30; i<45; i++){
					for(int j=0; j<80; j++){
						if(socket_buffer_cnt >= 1200){
							socket_buffer_cnt = 0;
						}

						socket_buffer_c[socket_buffer_cnt] = (uint8_t)transformed_buffer[j][i];

						if(socket_buffer_cnt < 1200){
							socket_buffer_cnt++;
						}
					}
				}
				//Send buffer C
				socket_data = send(socket_newsockfd, socket_buffer_c, (SOCKET_MAXDATASIZE/4), 0);

				if(socket_data < 0){
					printf("ERROR: Data not sent\nExiting...\n\n");
					exit(1);
				}
				//---------------------------------END OF BUFFER C------------------------------------//
				break;

			case 3:
				//--------------------------------START OF BUFFER D-----------------------------------//
				socket_buffer_cnt = 0;

				//Fill the buffer D with row 46-60
				for(int i=45; i<60; i++){
					for(int j=0; j<80; j++){
						if(socket_buffer_cnt >= 1200){
							socket_buffer_cnt = 0;
						}

						socket_buffer_d[socket_buffer_cnt] = (uint8_t)transformed_buffer[j][i];

						if(socket_buffer_cnt < 1200){
							socket_buffer_cnt++;
						}
					}
				}

				//Send buffer D
				socket_data = send(socket_newsockfd, socket_buffer_d, (SOCKET_MAXDATASIZE/4), 0);
				
				if(socket_data < 0){
					printf("ERROR: Data not sent\nExiting...\n\n");
					exit(1);
				}
				//---------------------------------END OF BUFFER D------------------------------------//
				break;

			case 4:
				//--------------------------------START OF TEMP SEND----------------------------------//
				//Calculate the temperature; formula used: Temp = (value-lowestValue which a pixel can have) / coeff - 10*C;
				lepton_min_temp = (((minValue-6832) / 32.0) - 10) * 10;
				lepton_max_temp = (((maxValue-6832) / 32.0) - 10) * 10;
				lepton_center_temp = (((centerValue - 6832) / 32.0) - 10) * 10;

				//Fill the buffer with temperature
					 [0] = lepton_min_temp;
				socket_buffer_sendTemp[1] = lepton_max_temp;
				socket_buffer_sendTemp[2] = lepton_center_temp;
				socket_buffer_sendTemp[3] = 1;
				socket_buffer_sendTemp[4] = 1;
				socket_buffer_sendTemp[5] = 1;

				printf("[1] minValue : %d\n", minValue);
				printf("[2] maxValue : %d\n", maxValue);
				printf("[3] centerValue : %d\n\n", centerValue);

				//Send min, max and center temperatures
				socket_data = send(socket_newsockfd, socket_buffer_sendTemp, 12, 0);
				if(socket_data<0){
					printf("ERROR: Data not sent\nExiting...\n\n");
					exit(1);
				}
				//---------------------------------END OF TEMP SEND----------------------------------//
				break;
			}
			socket_buffer_stage++;
		}
	}

	//Close the socket
	close(socket_newsockfd);
	close(socket_sockfd);
	SpiClosePort(1);
	return 0;
}

