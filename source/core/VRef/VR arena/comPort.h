#ifndef _COMPORT
#define _COMPORT

#include "errormsg.h"

#define SYNC_MODE 0
#define ASYNC_MODE 1
#define COM_PORT_SPEED CBR_57600
//#define COM_PORT_SPEED CBR_115200
//#define COM_PORT_SPEED CBR_256000



struct UART 
{
	
	int state;							// хранит в себе результат инициализации
	int mode;							// режим работы (0-синхронный, 1-асинхронный)
	LPCTSTR sPortName;					// номер ком порта
	HANDLE hSerial;						// указатель на открытое соединение(COM-порт)
	OVERLAPPED overlapped;				// для асинхронного режима
	
	UART(int _mode);
	UART(LPCTSTR portNumber, int _mode);

	int init();					// автоматическая инициализация com-соединения в зависимости от выбранного режима (mode)
	int init_async();			// инициализация при асинхронном режиме
	int init_sync();			// инициализация при синхронном режиме
	void close();				// закрытие com-соединения
	void test();				// заглушка
	char read();				// автоматический выбор чтения из com-порта в зависимости от выбранного режима (mode)
	char read_sync();			// чтение символа при синхронном режиме
	char read_async();			// чтение символа при асинхронном режиме
	int getDataToMemAreaUntil(unsigned char *pMemArea, unsigned char ch);	// пишет в указаное место (*pMemArea) до тех пор пока не встретит указаный символ (ch), возвращает количество записаных элементов
	int getDataToMemArea(unsigned char *pMemArea, int size);				// пишет в указаное место (*pMemArea) указаное количество символов (size)
	char write(char cwinp);		// заглушка
	
	~UART();
};


#endif