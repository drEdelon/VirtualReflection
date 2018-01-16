#include "accelMatchBuff.h"
#include <iostream>

#define DELTA_TIMESTAMP 100

AccelMatchCalc Specimen;

	AccelMatchCalc::AccelMatchCalc()
	{
		accelDataBuff.init();
		lastTime = 0;
	}



	//наполнение

	void AccelMatchCalc::put(MATCHFRAME data)
	{
		if ((lastTime < data.timestmp)  && ((data.timestmp - lastTime) < DELTA_TIMESTAMP))
		{
			AccelMatchCalc::accelDataBuff.forcePut(data);
		}
		lastTime = data.timestmp;
	}

	//удаление

	void AccelMatchCalc::del()
	{
		accelDataBuff.del();
	}

	//возврат первого елемента

	MATCHFRAME AccelMatchCalc::readFirst()
	{
		return accelDataBuff.read();
	}


	//возврат последнего елемента

	MATCHFRAME AccelMatchCalc::readLast()
	{
		return accelDataBuff.read(accelDataBuff.infill() - 1);
	}

	
	//проверка на принадлежность временному диапазону 

	int AccelMatchCalc::timeRangeChecking(unsigned long time)
	{
		MATCHFRAME firstTmp = readFirst();
		MATCHFRAME lastTmp = readLast();
		if ((time < firstTmp.timestmp) || (time > lastTmp.timestmp)) return OUT_OF_RANGE;
		return ERROR_OK;
	}

	

	//поиск индекса буффера для заданного времени 

	int AccelMatchCalc::findIndex(unsigned long time)
	{
		MATCHFRAME tmp;
		int begin=0, end = SIZE_OF_ACCEL_MATH_BUFF, half;
		while (true)
		{
			half = (end-begin)/2;
			tmp = accelDataBuff.read(begin + half);
			if (tmp.timestmp == time) return (begin + half);
			tmp.timestmp > time ? begin += half : end -= half;
			if ((end - begin) == 0) return begin;
			if ((end - begin) == 1) 
			{
				MATCHFRAME tmpBegin = accelDataBuff.read(begin);
				MATCHFRAME tmpEnd = accelDataBuff.read(end);

				if ((time - tmpBegin.timestmp) < (tmpEnd.timestmp - time))  return begin;
				else return end; 
			}
		}
			
	}

	//возврат елемента по выбранному времени

	MATCHFRAME AccelMatchCalc::readPresetTime(unsigned long time)
	{
		MATCHFRAME err;
		err.timestmp = 0;
		if (timeRangeChecking(time) != ERROR_OK) return err;

		return accelDataBuff.read(findIndex(time));
	}
	
	//возврат количества елементов по диапазону 
	
	int AccelMatchCalc::readRangeOfTime(unsigned long firstTime, unsigned long lastTime)
	{
		if (timeRangeChecking(firstTime) != ERROR_OK) return -1;
		if (timeRangeChecking(lastTime) != ERROR_OK) return -1;
		return (findIndex(lastTime) - findIndex(firstTime));


	}
	//возврат елементов по диапазону 

	//MATCHFRAME getRangeOfTime()
	//{

	//}

	void init_thread_data_in()
	{
		std::cout << "init thread" << std::endl;
		uartThreadON(&Specimen.accelDataBuff);
	}
