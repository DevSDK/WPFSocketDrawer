using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SocketDrawer
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        SocketDrawer Drawer;
        //RGB Buffer [ R, G, B, R, G, B, R, G, B, R .... ]
        byte[] recImage = new byte[60 * 80 * 3];
        public MainWindow()
        {
            InitializeComponent();

            Drawer = new SocketDrawer("211.224.201.147", Arguments.Port, onUpdate);
            Thread thread = new Thread(Drawer.Run);
            thread.IsBackground = false;
            thread.Start();
        }
        
        //Called by NetworkThread with received data. 
        public void onUpdate(byte[] Data)
        {
            if (Data == null)
                return;

            for (int i = 0; i < 60; i++)
            {
                for (int j = 0; j < 80; j++)
                {
                    //Received data pass to Filler_Grading
                    recImage[(i * 80 + j) * 3] = Filler_Grading.Data[3 * Data[i * 80 + j] + 2];     //R 
                    recImage[(i * 80 + j) * 3 + 1] = Filler_Grading.Data[3 * Data[i * 80 + j] +1];  //G
                    recImage[(i * 80 + j) * 3 + 2] = Filler_Grading.Data[3 * Data[i * 80 + j]];     //B
                }
            }
            try
            {
                //Update UI on the UI Threada, If try to update on the Network thread, It'll be crashed.
                Application.Current.Dispatcher.BeginInvoke(new Action(() => CenterTemp.Content = Drawer.temp_data[2]));
                Application.Current.Dispatcher.BeginInvoke(new Action(() => Max_temp.Content = Drawer.temp_data[0]));
                Application.Current.Dispatcher.BeginInvoke(new Action(() => Min_Temp.Content = Drawer.temp_data[1]));
                Application.Current.Dispatcher.BeginInvoke(new Action(() => Image_Output.Source = LoadImage(80, 60, recImage)));
            }
            catch(Exception)
            {
                Environment.Exit(0);
            }
        }
        //RGB Byte array to BitmapSource.
        private BitmapSource LoadImage(int width, int height, byte[] imageData)
        {
            var format = PixelFormats.Rgb24;
            var stride = width * (format.BitsPerPixel / 8);
            return BitmapSource.Create(width, height, 80, 80, format, null, imageData, stride);
        }
    }
}
