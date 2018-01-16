#ifndef _CIRCLEBUFFER
#define _CIRCLEBUFFER

#include "errormsg.h"

#define SIZE_OF_CIRCLE_BUFFER 1000
#define uchar unsigned char

struct CBUFF
{
	uchar circBuff[SIZE_OF_CIRCLE_BUFFER];		// размер буфера в байтах
	int cntB, cntE;								// счетчики начала и конца буфера
	int takenPlaceBuff;							// количество данных в буфере
	bool readAllow, writeAllow;					// запрет на чтение и запись
	bool threadON;								// индикатор работы потока
	CBUFF::CBUFF();

	void beginMove(int step);					// перемещение начала буфера на величину (step)
	void endMove(int step);						// перемещение конца буфера на величину (step)
	int infill();								// возвращает величину наполнености буфера
	void del();									// удал€ет первый элемент буфера
	void del(int step);							// удал€ет step первых элементов буфера
	void delete_all();							// опустошает буфер
	uchar read();								// возвращает первый элемент буфера не удал€€ его
	uchar read(int step);						// возвращает первый + step элемент буфера не удал€€ его
	void put(uchar sReceivedChar);				// помещает елемент в конец буфера
	void forcePut(uchar sReceivedChar);			// помещает елемент в конец буфера, если буфер заполнен - записывает на место первого элемента 
	int address(WORD cur, WORD dest);			// возвращает номер элемента (cur) со здвигом (dest). Ќеобходим дл€ реализации "кольца"(правильного перехода через границу буфера)

};

#endif