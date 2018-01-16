#include "proc.h"

#define KMSGNUM 20
struct procUnit 
{
	UINT index;
	//void (*pproc)(WPARAM wParam, LPARAM lParam);
	MSGUINT pproc;
};
procUnit msgProc[KMSGNUM]; // хранит массив указателей на функции обработки устройств ввода
	
int procCnt=0;

void wlpNOP(WPARAM	wParam,	LPARAM	lParam) // процедура затычка
{ 
	printf("nop\n");
} 

int findLastProc()	//возвращает указатель на первый нез€н€тый елемент массива
{
	return procCnt;
}

void procListInit()	// начальна€ инициализаци€ массива затычками
{
	for (int indx=0; indx<KMSGNUM; indx++)
	{
		procCnt=0;
		msgProc[indx].index=0;
		msgProc[indx].pproc=wlpNOP;
	}
}


int findIndexProc(UINT umsg)	// поиск нужной функции в массиве по коду сообщени€(index)
{
	for (int indx=0; indx<findLastProc(); indx++)
	{
		if (msgProc[indx].index==umsg) 
		{
			return indx;
		}
	}
	return -1;
}

int addMsgProc(UINT umsg, MSGUINT procp)	// наполн€ет €чейку массива нужными данными
{
	procp(0,0);
	if (procCnt==(KMSGNUM-1)) { return PROCLIST_IS_FULL; }
	else
	{
		msgProc[procCnt].index=umsg;
		msgProc[procCnt].pproc=procp;
		procCnt++;
		return ERROR_OK;
	}
}
int callProc(UINT umsg, WPARAM wParam, LPARAM lParam)	//вызов функции по номеру сообщени€(index)
{
	int fmsg=findIndexProc(umsg);
	if (fmsg>=0)
	{
		msgProc[fmsg].pproc(wParam, lParam);
		return ERROR_OK;
	}
	else 
	{
		return SOMETHING_WRONG; 
	}
}

//};