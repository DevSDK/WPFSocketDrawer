#ifndef FLIR_CROMATIC
#define FLIR_CROMATIC
const int flir_scale[] = {
//B		G		R
24	,	17	,	0	,
25	,	16	,	0	,
26	,	15	,	0	,
27	,	14	,	0	,
28	,	13	,	0	,
29	,	12	,	0	,
30	,	11	,	0	,
31	,	10	,	0	,
32	,	9	,	0	,
33	,	8	,	0	,
34	,	7	,	0	,
35	,	6	,	0	,
36	,	5	,	0	,
37	,	4	,	0	,
38	,	3	,	0	,
39	,	2	,	0	,
40	,	1	,	0	,
41	,	0	,	0	,
42	,	0	,	0	,
43	,	0	,	0	,
44	,	0	,	0	,
45	,	0	,	0	,
46	,	0	,	0	,
47	,	0	,	0	,
48	,	0	,	0	,
49	,	0	,	0	,
50	,	0	,	0	,
51	,	0	,	0	,
52	,	0	,	0	,
53	,	0	,	0	,
54	,	0	,	0	,
55	,	0	,	0	,
56	,	0	,	0	,
57	,	0	,	0	,
58	,	0	,	0	,
59	,	0	,	0	,
60	,	0	,	0	,
61	,	0	,	0	,
62	,	0	,	0	,
63	,	0	,	0	,
64	,	0	,	0	,
65	,	0	,	0	,
66	,	0	,	0	,
67	,	0	,	0	,
68	,	0	,	0	,
69	,	0	,	0	,
70	,	0	,	0	,
71	,	0	,	0	,
72	,	0	,	0	,
73	,	0	,	0	,
74	,	0	,	0	,
75	,	0	,	0	,
76	,	0	,	0	,
77	,	0	,	0	,
78	,	0	,	0	,
79	,	0	,	0	,
80	,	0	,	0	,
81	,	0	,	0	,
82	,	0	,	0	,
83	,	0	,	0	,
84	,	0	,	2	,
85	,	0	,	4	,
86	,	0	,	6	,
87	,	0	,	8	,
88	,	0	,	10	,
89	,	0	,	12	,
90	,	0	,	14	,
91	,	0	,	16	,
92	,	0	,	18	,
93	,	0	,	20	,
94	,	0	,	22	,
95	,	0	,	24	,
96	,	0	,	26	,
97	,	0	,	28	,
98	,	0	,	30	,
99	,	0	,	32	,
100	,	0	,	34	,
101	,	0	,	36	,
102	,	0	,	38	,
103	,	0	,	40	,
104	,	0	,	42	,
105	,	0	,	44	,
106	,	0	,	46	,
107	,	0	,	48	,
108	,	0	,	50	,
109	,	0	,	52	,
110	,	0	,	54	,
111	,	0	,	56	,
112	,	0	,	58	,
113	,	0	,	60	,
114	,	0	,	62	,
115	,	0	,	64	,
116	,	0	,	66	,
117	,	0	,	68	,
118	,	0	,	70	,
119	,	0	,	72	,
120	,	0	,	74	,
121	,	0	,	76	,
122	,	0	,	78	,
123	,	0	,	80	,
124	,	0	,	82	,
125	,	0	,	84	,
126	,	0	,	86	,
127	,	0	,	88	,
128	,	0	,	90	,
129	,	0	,	92	,
130	,	0	,	94	,
131	,	0	,	96	,
132	,	0	,	98	,
133	,	0	,	100	,
134	,	0	,	102	,
135	,	0	,	104	,
136	,	0	,	106	,
137	,	0	,	108	,
138	,	0	,	110	,
139	,	0	,	112	,
140	,	0	,	114	,
141	,	0	,	116	,
142	,	0	,	118	,
143	,	0	,	120	,
144	,	0	,	122	,
145	,	0	,	124	,
146	,	0	,	126	,
147	,	0	,	128	,
148	,	0	,	130	,
149	,	0	,	132	,
150	,	0	,	134	,
151	,	0	,	136	,
152	,	2	,	138	,
153	,	4	,	140	,
154	,	6	,	142	,
155	,	8	,	144	,
156	,	10	,	146	,
157	,	12	,	148	,
158	,	14	,	150	,
159	,	16	,	152	,
160	,	18	,	154	,
161	,	20	,	156	,
162	,	22	,	158	,
163	,	24	,	160	,
164	,	26	,	162	,
165	,	28	,	164	,
166	,	30	,	166	,
167	,	32	,	168	,
168	,	34	,	170	,
168	,	36	,	172	,
168	,	38	,	174	,
168	,	40	,	176	,
168	,	42	,	178	,
168	,	44	,	180	,
168	,	46	,	182	,
168	,	48	,	184	,
167	,	50	,	186	,
166	,	52	,	188	,
165	,	54	,	190	,
164	,	56	,	192	,
163	,	58	,	194	,
162	,	60	,	196	,
161	,	62	,	198	,
160	,	64	,	200	,
156	,	66	,	202	,
152	,	68	,	204	,
148	,	70	,	206	,
144	,	72	,	208	,
140	,	74	,	210	,
136	,	76	,	212	,
132	,	78	,	214	,
128	,	80	,	216	,
124	,	82	,	218	,
120	,	84	,	220	,
116	,	86	,	222	,
112	,	88	,	224	,
108	,	90	,	226	,
104	,	92	,	228	,
100	,	94	,	230	,
96	,	96	,	232	,
92	,	98	,	234	,
88	,	100	,	236	,
84	,	102	,	238	,
80	,	104	,	240	,
76	,	106	,	242	,
72	,	108	,	244	,
68	,	110	,	246	,
64	,	112	,	248	,
60	,	114	,	250	,
56	,	116	,	252	,
52	,	118	,	254	,
48	,	120	,	255	,
44	,	122	,	255	,
40	,	124	,	255	,
36	,	126	,	255	,
32	,	128	,	255	,
28	,	130	,	255	,
24	,	132	,	255	,
20	,	134	,	255	,
16	,	136	,	255	,
12	,	138	,	255	,
8	,	140	,	255	,
4	,	142	,	255	,
0	,	144	,	255	,
1	,	146	,	255	,
2	,	148	,	255	,
3	,	150	,	255	,
4	,	152	,	255	,
5	,	154	,	255	,
6	,	156	,	255	,
10	,	158	,	255	,
15	,	160	,	255	,
20	,	162	,	255	,
25	,	164	,	255	,
30	,	166	,	255	,
35	,	168	,	255	,
40	,	170	,	255	,
45	,	172	,	255	,
50	,	174	,	255	,
55	,	176	,	255	,
60	,	178	,	255	,
65	,	180	,	255	,
70	,	182	,	255	,
75	,	184	,	255	,
80	,	186	,	255	,
85	,	188	,	255	,
90	,	190	,	255	,
95	,	192	,	255	,
100	,	194	,	255	,
105	,	196	,	255	,
110	,	198	,	255	,
115	,	200	,	255	,
120	,	202	,	255	,
125	,	204	,	255	,
130	,	206	,	255	,
135	,	208	,	255	,
140	,	210	,	255	,
145	,	212	,	255	,
150	,	214	,	255	,
155	,	216	,	255	,
160	,	218	,	255	,
165	,	220	,	255	,
170	,	222	,	255	,
175	,	224	,	255	,
180	,	226	,	255	,
185	,	228	,	255	,
190	,	230	,	255	,
195	,	232	,	255	,
200	,	234	,	255	,
205	,	236	,	255	,
210	,	238	,	255	,
215	,	240	,	255	,
220	,	242	,	255	,
225	,	244	,	255	,
230	,	246	,	255	,
235	,	248	,	255	,
240	,	250	,	255	,
245	,	252	,	255	,
250	,	254	,	255	,
255	,	255	,	255	,

};
#endif
