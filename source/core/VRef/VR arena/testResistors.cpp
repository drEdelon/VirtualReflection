#include "testResistors.h"
#include <iostream>
#include <windows.h>

UART ResMass("COM2", 0);
int flag = 0;
int headerForRes()
{
	int cnt = 0;
	while (cnt < 100)
	{
		if (ResMass.read() == 'F')
		{
			if (ResMass.read() == 'G')
			{
				return ERROR_OK;
			}
		}
		cnt++;
	}
	return 1;
}
int getDataComForRes(unsigned char &dataFromResistors, int sizeOfMemArea)
{
	unsigned char *pDataFromResistors = &dataFromResistors;
	//if (ResMass.init() == ERROR_OK)
	if (!flag){ResMass.init();flag = 1;}
		if (headerForRes() == ERROR_OK)
			if	(ResMass.getDataToMemArea(pDataFromResistors, sizeOfMemArea) == READ_OK)
			{
				//ResMass.close();	
				return ERROR_OK;
			}
	ResMass.close();
	return SOMETHING_WRONG;
}