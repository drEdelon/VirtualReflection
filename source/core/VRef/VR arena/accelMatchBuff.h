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

	void put(MATCHFRAME data);							//наполнение
	void del();											//удаление
	MATCHFRAME readFirst();								//возврат первого елемента
	MATCHFRAME readLast();								//возврат последнего елемента
	int timeRangeChecking(unsigned long time);			//проверка на принадлежность временному диапазону 
	int findIndex(unsigned long time);					//поиск индекса буффера для заданного времени 
	MATCHFRAME readPresetTime(unsigned long time);		//возврат елемента по выбранному времени
	int readRangeOfTime(unsigned long firstTime, unsigned long lastTime);	//возврат количества елементов по диапазону 
};

void init_thread_data_in();










#endif