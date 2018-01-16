#include "circleBuffer.h"
#include <iostream>

CBUFF::CBUFF()
{	
	cntB=0;
	cntE=0; 
	takenPlaceBuff=0;
	readAllow=1; 
	writeAllow=1;
	threadON = 1;
}

void CBUFF::beginMove(int step)
{
	cntB = address(cntB, step);
}
void CBUFF::endMove(int step)
{
	cntE = address(cntE, step);
}

int CBUFF::infill()
{
	return takenPlaceBuff;
}

void CBUFF::del()
{
	del(1);
}
void CBUFF::del(int step)
{
	if (step < takenPlaceBuff)
	{
		lastError = ERROR_OK;
		beginMove(step);
		takenPlaceBuff -= step;
	}
	else {lastError = CIRCLE_BUFF_EMPTY;}
}

void CBUFF::delete_all()
{
	while(readAllow == 0){};
	readAllow = 0;
	while(writeAllow == 0){};
	writeAllow = 0;

	CBUFF::del(takenPlaceBuff);
	readAllow = 1; 
	writeAllow = 1;

}

uchar CBUFF::read()
{
	return read(0);
}
uchar CBUFF::read(int step)
{
	if (step < takenPlaceBuff)
	{
		lastError = ERROR_OK;
		return circBuff[address(cntB,step)];
	}
	else {lastError = READ_DATA_LESS_THEN_YOU_NEED;}
	return 0;
}
int CBUFF::address(WORD cur, WORD dest)
{
	if ((cur+dest)<SIZE_OF_CIRCLE_BUFFER)	{ return cur+dest; }
	else						{ return (cur+dest)-SIZE_OF_CIRCLE_BUFFER;}
}
void CBUFF::put(uchar sReceivedChar)
{
	if (infill() == (SIZE_OF_CIRCLE_BUFFER))
	{
		lastError = CIRCLE_BUFF_FULL;
		//forcePut(sReceivedChar);
		//std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; 
	}
	else
	{
		lastError = ERROR_OK;
		circBuff[cntE] = sReceivedChar;
		endMove(1);
		takenPlaceBuff++;
	}
}
void CBUFF::forcePut(uchar sReceivedChar)
{
	if(takenPlaceBuff == (SIZE_OF_CIRCLE_BUFFER)) del();
	put(sReceivedChar);
}
