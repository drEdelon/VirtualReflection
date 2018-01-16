
#include "TODO.h"
#include "v_sys.h"
#include "v_input.h"
#include "v_output.h"
#include "v_calc.h"
#include "..\userdef.h"
#include "accelMatchBuff.h"
//#include <iostream>

#include <ctime>

    clock_t start_time = clock(); //Запускаем таймер.
    double elapsed;
   

float cam_rot=0.5f;

float q[] = {0,0,0,0};
float roll = 0;
float pitch = 0;
float yaw = 0;

int mInit()
{
	VisMode=VIS_CUBE;
	//VisMode=VIS_GRAPH;
	//VisMode=VIS_HAND;
	//VisMode=VIS_QUAT;
	//VisMode=VIS_SPHERE;
	//VisMode=VIS_VECTORS;

	lastError=sysinit();
	if(lastError) return lastError;

	if(lastError) return lastError;

	lastError=outputinit();

	if(lastError) return lastError;

	lastError=calcinit();
	if(lastError) return lastError; 

	else return lastError;
}
void mRestore()
{
	sysrest();      //системная инициялизация
	inputrest();	// модуль ввода.  
	outputrest();	//вывод
	calcrest();		//мат инструментарий
}


void mainLoop(void)
{
	U_QUAT quat_memarea;
	QUAT_AND_ANGLES q_a = {0};
	q_a.qw = 1;
	MATCHFRAME tempval;
	brush.initBrush();
	brush.recordStart();

	switch (VisMode)
	{
		case VIS_CUBE:
 		{
			
			initSkyBox();
			printf("enter to CUBE loop\n");

			init_thread_data_in();
			while (!appQuit)
			{
				if (winmsgproc()==NOWINMSGPROC)
				{	
					//brush.setPos(V3Df((float)(rand()% 30),(float)(rand()% 30),(float)(rand()% 30)));
					//brush.setB(brush.tra+V3Df(0.01,0.001,0.1),brush.rot+V3Df(1,0.5,0.25));
					//timeBufqwegaccf();
					//printf("%d %d %d\n",myBase.ax,myBase.ay,myBase.az);
					//brush.setB(brush.tra+V3Df(((rand()% 301)-150)*0.001f,((rand()% 301)-150)*0.001f,((rand()% 301)-150)*0.001f),brush.rot);
					
					//while (parse(&tempval, 1) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					//{}
					//	c_send_data(tempval);
					//	flag();



					if (parse(&tempval, PALM_PACKET) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					{
						c_send_data(tempval);

						
					}


					//if (keys[VK_RIGHT])		{zobj = zobj - cam_rot;}
					//if (keys[VK_LEFT])		{zobj = zobj + cam_rot;}
					if (keys[VK_RIGHT])		{brush.rot = brush.rot - V3Df(0, 0, 0.3);}
					if (keys[VK_LEFT])		{brush.rot = brush.rot + V3Df(0, 0, 0.3);}
					if (keys[VK_UP])		{brush.rot = brush.rot - V3Df(0.3, 0, 0);}
					if (keys[VK_DOWN])		{brush.rot = brush.rot + V3Df(0.3, 0, 0);}
					//if (keys[VK_UP])		{yobj=yobj-cam_rot;}
					//if (keys[VK_DOWN])		{yobj=yobj+cam_rot;}
					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (MzDelta!=0) 
					{
						Cdist+=0.1f*MzDelta;
						if (Cdist<0.1f){Cdist=0.1f;}
						MzDelta=0;
					}
					if (mState&&MK_LBUTTON)
					{
						xobj+=float((MxPos)*0.10);
						if (MyPos>90) {MyPos=90;}
						if (MyPos< -90) {MyPos= -90;}
						yobj+=float((MyPos)*0.1); 
						SetCursorPos((wwidth/2)+wxpos, (wheight/2)+wypos);
					}  
					if (keys['F'])	{	folow= true;	}
					if (keys['G'])	{	folow= false;	}
					if (keys['A'])	{	zobj = 0.0; yobj = 0.0; xobj = 0.0;	}
					if (keys['Q'])	{	brush.setPos(0,0,0);}
					if (keys['W'])	{	brush.setRot(0,0,0);}
					if (keys['C'])	{	brush.rec.track.init();}
			

					//if (keys['V'])	{	brush1.track.init();}
					//if (keys['Z'])	{	modeAxelGiro=true;}
					//if (keys['X'])	{	modeAxelGiro=false;}
					
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}
		case VIS_GRAPH:
		{
			//init_parser(void *_memarea);
			init_thread_data_in();
			MATCHFRAME rcvr={0,0,0,0,0,0,0};
			MATCHFRAME rcvrs=rcvr;
			printf("enter to GRAPH loop\n");
			
			struct DVA_INTEGRALA
			{
				short axel, speed, dist;
			}dva_integrala;

			int tick = 0;
			float SFACTOR = (1 / 32768.0);
			int flag = 0;
			while (!appQuit)
			{
				
					if (parse(&dva_integrala, INTEGRAL_PACKET) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					{
						//c_send_data(tempval);
						//norm = sqrt((float)tempval.mp.ax * (float)tempval.mp.ax + (float)tempval.mp.ay * (float)tempval.mp.ay + (float)tempval.mp.az * (float)tempval.mp.az);
						//ax = tempval.mp.ax / norm;
						//ay = tempval.mp.ay / norm;
						//az = tempval.mp.az / norm;

						//norm = sqrt((float)tempval.mp.gx * (float)tempval.mp.gx + (float)tempval.mp.gy * (float)tempval.mp.gy + (float)tempval.mp.gz * (float)tempval.mp.gz);
						//gx = tempval.mp.gx / norm;
						//gy = tempval.mp.gy / norm;
						//gz = tempval.mp.gz / norm;
						elapsed = (clock() - start_time);
						tick = 0;
						if (elapsed >= 100)
						{
							start_time += 100;
							tick = 1;
						}
						
						if (!flag) brush.setB((float)dva_integrala.axel * SFACTOR, (float)dva_integrala.speed * SFACTOR, (float)dva_integrala.dist * SFACTOR, 0.0, 0.0, (float)tick);
					}
				if (winmsgproc()==NOWINMSGPROC)
				{	
					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (keys['Q'])	{	acel_draw= true;	}
					if (keys['A'])	{	acel_draw= false;	}
					if (keys['E'])	{	giro_draw= true;	}
					if (keys['D'])	{	giro_draw= false;	}
					if (keys['M'])	{	brush.setB(0,0,0,0,0,0);}
					if (keys['C'])	{	brush.rec.track.init();}
					if (keys['S'])	{	flag = 1;}
					if (keys['P'])	{	flag = 0;}
//					c_send_data(myTmpBuff.parse());
					//while (parse(&tempval, 1) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					//{
					//	c_send_data(tempval);
					//}
				//	printf("%i\n",clock()); //Запускаем таймер.

					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}
		case VIS_HAND:
		{
			initSkyBox();
			GLOVE glove = {0};
			MATCHFRAME rcvr={0,0,0,0,0,0,0};
			MATCHFRAME rcvrs=rcvr;
			printf("enter to HAND loop\n");
			init_thread_data_in();
			while (!appQuit)
			{
				if (winmsgproc()==NOWINMSGPROC)
				{	
					if (keys[VK_RIGHT])		{zobj = zobj - cam_rot;}
					if (keys[VK_LEFT])		{zobj = zobj + cam_rot;}
					if (keys[VK_UP])		{yobj=yobj-cam_rot;}
					if (keys[VK_DOWN])		{yobj=yobj+cam_rot;}
					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (MzDelta!=0) 
					{
						Cdist+=0.1f*MzDelta;
						if (Cdist<0.1f){Cdist=0.1f;}
						MzDelta=0;
					}
					if (mState&&MK_LBUTTON)
					{
						xobj+=float((MxPos)*0.10);
						if (MyPos>90) {MyPos=90;}
						if (MyPos< -90) {MyPos= -90;}
						yobj+=float((MyPos)*0.1); 
						SetCursorPos((wwidth/2)+wxpos, (wheight/2)+wypos);
					}  
					if (keys['Q'])	
					{	
						cpoint++;
						printf("%d\n",cpoint);
						while (keys['Q']){winmsgproc();}
					}
					if (keys['W'])	
					{
						cpoint--;
						printf("%d\n",cpoint);
						while (keys['W']){winmsgproc();}
					}
					
					//if (getDataComForRes(dataFromResistors[0], 24) == ERROR_OK)
					
					//if (parse(&tempval, PALM_PACKET) == READ_OK)
					if (parse(&glove, GLOVE_PACKET) == READ_OK)
					{
						for(int i = 0; i < 24; i++)
						{
							dataFromResistors[i] = glove.finger[i];
						}

					printf("%X %X %X %X  %X %X %X %X\n",
						dataFromResistors[0],dataFromResistors[1],
						dataFromResistors[2],dataFromResistors[3],
						dataFromResistors[4],dataFromResistors[5],
						dataFromResistors[6],dataFromResistors[7]);
					printf("%X %X %X %X  %X %X %X %X\n",
						dataFromResistors[8],dataFromResistors[9],
						dataFromResistors[10],dataFromResistors[11],
						dataFromResistors[12],dataFromResistors[13],
						dataFromResistors[14],dataFromResistors[15]);
					printf("%X %X %X %X  %X %X %X %X\n",
						dataFromResistors[16],dataFromResistors[17],
						dataFromResistors[18],dataFromResistors[19],
						dataFromResistors[20],dataFromResistors[21],
						dataFromResistors[22],dataFromResistors[23]);
					printf("\n");
					}
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}
		case VIS_QUAT:
		{
			initSkyBox();

			printf("enter to QUAT loop\n");
			init_thread_data_in();
			while (!appQuit)
			{
				if (winmsgproc()==NOWINMSGPROC)
				{	
					if (parse(&quat_memarea, QUAT_PACKET) == READ_OK)  
					{
						std::cout << quat_memarea.q_a.roll * 57.295779  << " " << quat_memarea.q_a.pitch * 57.295779 << " " << quat_memarea.q_a.yaw * 57.295779 << " " << std::endl;
						

						brush.rot = V3Df(-quat_memarea.q_a.pitch * 57.295779, -quat_memarea.q_a.yaw * 57.295779, -quat_memarea.q_a.roll * 57.295779);
					}
		
					if (keys[VK_RIGHT])		{brush.rot = brush.rot - V3Df(0, 0, 0.3);}
					if (keys[VK_LEFT])		{brush.rot = brush.rot + V3Df(0, 0, 0.3);}
					if (keys[VK_UP])		{brush.rot = brush.rot - V3Df(0.3, 0, 0);}
					if (keys[VK_DOWN])		{brush.rot = brush.rot + V3Df(0.3, 0, 0);}

					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (MzDelta!=0) 
					{
						Cdist+=0.1f*MzDelta;
						if (Cdist<0.1f){Cdist=0.1f;}
						MzDelta=0;
					}
					if (mState&&MK_LBUTTON)
					{
						xobj+=float((MxPos)*0.10);
						if (MyPos>90) {MyPos=90;}
						if (MyPos< -90) {MyPos= -90;}
						yobj+=float((MyPos)*0.1); 
						SetCursorPos((wwidth/2)+wxpos, (wheight/2)+wypos);
					}  
					if (keys['F'])	{	folow= true;	}
					if (keys['G'])	{	folow= false;	}
					if (keys['A'])	{	zobj = 0.0; yobj = 0.0; xobj = 0.0;	}
					if (keys['Q'])	{	brush.setPos(0,0,0);}
					if (keys['W'])	{	brush.setRot(0,0,0);}
					if (keys['C'])	{	brush.rec.track.init();}

					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}


		case VIS_SPHERE:
		{
			initSkyBox();
			printf("enter to SPHERE loop\n");


				brush.tra = V3Df(0.5,0.5,0.5);
				brush.rot = V3Df(40,30,20);
				brush.sz = V3Df(0.05f,0.01f,0.1f);
				brush.initBrush();
				struct FLOAT3
				{
					float x, y, z;
				}float3;

			init_thread_data_in();
			while (!appQuit)
			{
				if (winmsgproc()==NOWINMSGPROC)
				{	
					//brush.setPos(V3Df((float)(rand()% 30),(float)(rand()% 30),(float)(rand()% 30)));
					//brush.setB(brush.tra+V3Df(0.01,0.001,0.1),brush.rot+V3Df(1,0.5,0.25));
					//timeBufqwegaccf();
					//printf("%d %d %d\n",myBase.ax,myBase.ay,myBase.az);
					//brush.setB(brush.tra+V3Df(((rand()% 301)-150)*0.001f,((rand()% 301)-150)*0.001f,((rand()% 301)-150)*0.001f),brush.rot);
					
					//while (parse(&tempval, 1) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					//{}
					//	c_send_data(tempval);
					//	flag();



					if (parse(&float3, SPHERE_PACKET) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					{
						float SFACTOR=32768.0;
						brush.setPos(float3.x, float3.y, float3.z);
						//c_send_data(tempval);

						
					}


					//if (keys[VK_RIGHT])		{zobj = zobj - cam_rot;}
					//if (keys[VK_LEFT])		{zobj = zobj + cam_rot;}
					if (keys[VK_RIGHT])		{brush.rot = brush.rot - V3Df(0, 0, 0.3);}
					if (keys[VK_LEFT])		{brush.rot = brush.rot + V3Df(0, 0, 0.3);}
					if (keys[VK_UP])		{brush.rot = brush.rot - V3Df(0.3, 0, 0);}
					if (keys[VK_DOWN])		{brush.rot = brush.rot + V3Df(0.3, 0, 0);}
					//if (keys[VK_UP])		{yobj=yobj-cam_rot;}
					//if (keys[VK_DOWN])		{yobj=yobj+cam_rot;}
					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (MzDelta!=0) 
					{
						Cdist+=0.1f*MzDelta;
						if (Cdist<0.1f){Cdist=0.1f;}
						MzDelta=0;
					}
					if (mState&&MK_LBUTTON)
					{
						xobj+=float((MxPos)*0.10);
						if (MyPos>90) {MyPos=90;}
						if (MyPos< -90) {MyPos= -90;}
						yobj+=float((MyPos)*0.1); 
						SetCursorPos((wwidth/2)+wxpos, (wheight/2)+wypos);
					}  
					if (keys['F'])	{	folow= true;	}
					if (keys['G'])	{	folow= false;	}
					if (keys['A'])	{	zobj = 0.0; yobj = 0.0; xobj = 0.0;	}
					if (keys['Q'])	{	brush.setPos(0,0,0);}
					if (keys['W'])	{	brush.setRot(0,0,0);}
					if (keys['C'])	{	brush.rec.track.init();}
			

					//if (keys['V'])	{	brush1.track.init();}
					//if (keys['Z'])	{	modeAxelGiro=true;}
					//if (keys['X'])	{	modeAxelGiro=false;}
					
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}

		case VIS_VECTORS:
		{
				brush.tra = V3Df(0.5,0.5,0.5);
				brush.rot = V3Df(40,30,20);
				brush.sz = V3Df(0.0f,0.0f,0.0f);
				brush.initBrush();
			
			initSkyBox();
			printf("enter to VECTOR loop\n");



				struct VECTORS
				{
					float x1, y1, z1;
					float x2, y2, z2;
					float x3, y3, z3;
				}vectors;

				float *pvectors = &vectors.x1;

			init_thread_data_in();
			while (!appQuit)
			{
				if (winmsgproc()==NOWINMSGPROC)
				{	




					if (parse(pvectors, VECTORS_PACKET) == READ_OK)  // должен передаться адрес выделенного пространства и тип (1-ладонь, 2 пальцы)
					{
						float SFACTOR=32768.0;
						vectors_infill(pvectors, 3);
						//brush.setPos(float3.x, float3.y, float3.z);
						//c_send_data(tempval);

						
					}


					//if (keys[VK_RIGHT])		{zobj = zobj - cam_rot;}
					//if (keys[VK_LEFT])		{zobj = zobj + cam_rot;}
					if (keys[VK_RIGHT])		{brush.rot = brush.rot - V3Df(0, 0, 0.3);}
					if (keys[VK_LEFT])		{brush.rot = brush.rot + V3Df(0, 0, 0.3);}
					if (keys[VK_UP])		{brush.rot = brush.rot - V3Df(0.3, 0, 0);}
					if (keys[VK_DOWN])		{brush.rot = brush.rot + V3Df(0.3, 0, 0);}
					//if (keys[VK_UP])		{yobj=yobj-cam_rot;}
					//if (keys[VK_DOWN])		{yobj=yobj+cam_rot;}
					if (keys[VK_ESCAPE])	{appQuit=true;}
					if (MzDelta!=0) 
					{
						Cdist+=0.1f*MzDelta;
						if (Cdist<0.1f){Cdist=0.1f;}
						MzDelta=0;
					}
					if (mState&&MK_LBUTTON)
					{
						xobj+=float((MxPos)*0.10);
						if (MyPos>90) {MyPos=90;}
						if (MyPos< -90) {MyPos= -90;}
						yobj+=float((MyPos)*0.1); 
						SetCursorPos((wwidth/2)+wxpos, (wheight/2)+wypos);
					}  
					if (keys['F'])	{	folow= true;	}
					if (keys['G'])	{	folow= false;	}
					if (keys['A'])	{	zobj = 0.0; yobj = 0.0; xobj = 0.0;	}
					if (keys['Q'])	{	brush.setPos(0,0,0);}
					if (keys['W'])	{	brush.setRot(0,0,0);}
					if (keys['C'])	{	brush.rec.track.init();}
			

					
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			break;
		}

		
	

	}
}

#define WIDTH 80
#define HEIGHT 22

struct SOME
{
	void prtt()
	{
		printf("call ok\n");
	}
};

SOME a,b;

int wmain(int argc, wchar_t* argv[])
{	
	 //SOME c.prtt();
	if (mInit()==ERROR_OK) 
		mainLoop();
	else 
		printError();

	mRestore();
	return 0;
}



