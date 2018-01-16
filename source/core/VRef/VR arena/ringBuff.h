#ifndef _RINGBUFFT
#define _RINGBUFFT
#include "errormsg.h"

#ifndef WORD
	#define WORD  unsigned short
#else 
	#error WORD alredy exist!!!
#endif


template <typename RBNOD, int _RBUFFER_SIZE> 
struct RBUFFT
{
	bool readAllow, writeAllow;
	RBUFFT():begI(0),endI(0),fill(0),capacity(_RBUFFER_SIZE),readAllow(true),writeAllow(true),usefulArea(0),lockBegin(-1){}
	void init()
	{
		if (!writeAllow)	{ lastError=RINGBUFF_WRITE_IS_LOCKED; return; }
		begI=0;
		endI=0;
		fill=0;	
		usefulArea = 0;
		lockBegin = -1;
	};

	// ������� ������������ �������

	WORD infill()
	{
		return fill;
	}

	//������� ������� �������

	WORD Capacity()
	{
		return _RBUFFER_SIZE;
	}

	//������� ������� ����� � �������

	WORD free()
	{
		return _RBUFFER_SIZE-fill;
	}

	

	int del()
	{
		return del(1);
	}
	int del(WORD dNum)
	{
		if (!writeAllow)	{ return RINGBUFF_WRITE_IS_LOCKED; }
		if (fill<dNum)		{ return RINGBUFF_IS_FULL; }
	
		moveBeg(dNum);
		fill-=dNum;
		if(lockBegin != -1)
			if(usefulArea > 0)
			{
				usefulArea -= dNum;
				if(usefulArea <= 0){lockBegin = -1;}
			}
		
		return ERROR_OK;		
	}

	//������ ������ �� ������� � �������� ���������

	RBNOD read()	
	{	return read(0); }
	RBNOD read(WORD index)	
	{
		if (!readAllow)					{ lastError=RINGBUFF_READ_IS_LOCKED; return RBNOD(); }
		if ((fill==0)||(index>=fill))	{ lastError=RINGBUFF_IS_EMPTY;		 return RBNOD();	}
		return buff[address(begI,index)];	
	}

	//������� ������ �� ������ ������� � �� ���������

	RBNOD get()
	{
		RBNOD t=read();
		del();
		return t;
	}

	//�������� ������ � ����� �������

	int put(RBNOD pIn)
	{
		if (!writeAllow)	{ return RINGBUFF_WRITE_IS_LOCKED; }
		if (fill==capacity)	{ return RINGBUFF_IS_FULL; }
		buff[endI]=pIn;
		moveEnd(1);
		fill++;
		return ERROR_OK;
	}

	//�������� ������ � ����� ������� �� ������� ������(������ ��������� ��������)

	void forcePut(RBNOD pIn)
	{
		if (fill==capacity)	
		{ 
			del(); 
		}
		put(pIn);
	}

	//������ ������ ������
	
	int getBegin()
	{
		lockBegin = (signed short)begI;
		usefulArea = _RBUFFER_SIZE;
		return (int)begI;
	}

	//������� �������� �� �������

	RBNOD getGlobalIndexValue(int indx)
	{
		
		return buff[indx];
	}

private:
	RBNOD buff[_RBUFFER_SIZE];
	WORD begI,endI,fill,capacity;
	signed short lockBegin;
	int usefulArea;

	//�������� ����������� ������ � ����� � �������

	WORD address(WORD cur,WORD dest)
	{
		if ((cur+dest)<capacity)	{ return cur+dest; }
		else						{ return (cur+dest)-capacity;	}
	}

	//����������� ����� �������

	int moveEnd(WORD index)
	{
		if ((capacity-fill)<index)	{ return RINGBUFF_IS_FULL; }
		endI=address(endI,index);
		return ERROR_OK;
	}

	//����������� ������ �������

	int moveBeg(WORD index)
	{
		if (fill<index)	{ return RINGBUFF_IS_EMPTY; }
		begI=address(begI,index);
		return ERROR_OK;	
	}
};

#endif