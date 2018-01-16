#ifndef _ACCELMATCHBUFF
#define _ACCELMATCHBUFF

#include "Vccel\dataframe.h"
#include "ringbuff.h"
#include "errormsg.h"
#include "v_input.h"

struct AccelMatchCalc
{
	RBUFFT<MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF> accelDataBuff;
	unsigned long lastTime;

	AccelMatchCalc::AccelMatchCalc();

	void put(MATCHFRAME data);							//����������
	void del();											//��������
	MATCHFRAME readFirst();								//������� ������� ��������
	MATCHFRAME readLast();								//������� ���������� ��������
	int timeRangeChecking(unsigned long time);			//�������� �� �������������� ���������� ��������� 
	int findIndex(unsigned long time);					//����� ������� ������� ��� ��������� ������� 
	MATCHFRAME readPresetTime(unsigned long time);		//������� �������� �� ���������� �������
	int readRangeOfTime(unsigned long firstTime, unsigned long lastTime);	//������� ���������� ��������� �� ��������� 
};

void init_thread_data_in();










#endif