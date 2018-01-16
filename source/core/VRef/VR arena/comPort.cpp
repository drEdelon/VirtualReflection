#include "comPort.h"

#include <iostream>

using namespace std;


UART::UART(int _mode)
{	
	sPortName = "COM7";
	state = 1;
	mode = _mode;
};

UART::UART(LPCTSTR portNumber, int _mode)
{	
	sPortName = portNumber;
	state = 1;
	mode = _mode;
};

UART::~UART()
{
	//if (hSerial == NULL)
	////if (ReadFile(hSerial, 0, 0, 0, 0))
	//{
	//	close();
	//}
}

int UART::init_async()
{
	setlocale(LC_ALL,"Russian");
	hSerial = ::CreateFile(sPortName, GENERIC_READ , 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	
	overlapped.hEvent = 0;
	overlapped.Internal = 0;
	overlapped.InternalHigh = 0;
	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
	overlapped.Pointer = 0;
	//cout << "try to init com" << endl;
	
	if(hSerial==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
			return PORT_NOT_EXIST;
		}
		return PORT_NOT_OPEN;
	}


	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		return GET_STATE_ERR; 
	}
	dcbSerialParams.BaudRate=COM_PORT_SPEED;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	if(!SetCommState(hSerial, &dcbSerialParams))
	{
		return SERIAL_PORT_STATE_ERR; 
	}
	COMMTIMEOUTS timeouts ={0};
	if(!SetCommTimeouts(hSerial, &timeouts))
	{
		return SERIAL_PORT_TIMEOUTS_ERR; 
	}
	
	return 0;
}


int UART::init_sync()
{
	setlocale(LC_ALL,"Russian");
	hSerial = ::CreateFile(sPortName, GENERIC_READ , 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	//cout << "try to init com" << endl;
	int Error = GetLastError();
	if(hSerial==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
			return PORT_NOT_EXIST;
		}
		return PORT_NOT_OPEN;
	}


	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		return GET_STATE_ERR; 
	}
	//dcbSerialParams.BaudRate=CBR_115200;
	dcbSerialParams.BaudRate=CBR_57600;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	if(!SetCommState(hSerial, &dcbSerialParams))
	{
		return SERIAL_PORT_STATE_ERR; 
	}
	
	return 0;
}



int UART::init()
{
	int mediator = 0;

	if(mode == SYNC_MODE) mediator = init_sync();
	else mediator = init_async();

	return mediator;
}


void UART::close()
{
	CloseHandle( hSerial );
}
void UART::test()
{

}
char UART::read_sync()
{
	char sReceivedChar;
	DWORD iSize = 0;
	int cnt = 0;
	while(iSize <= 0)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
		cnt++;
		if (cnt%100 == 0) std::cout << "Incoming buffer is empty " << cnt << std::endl;
	}

	return sReceivedChar;
}

char UART::read_async()
{
	char sReceivedChar;
	DWORD iSize;

	ReadFile(hSerial, &sReceivedChar, 1, &iSize, &overlapped);  // получаем 1 байт
	
	return sReceivedChar;
}


char UART::read()
{
	char mediator = 0;

	if(mode == SYNC_MODE) mediator = read_sync();
	else mediator = read_async();

	return mediator;
}

int UART::getDataToMemArea(unsigned char *pMemArea, int size)
{
	unsigned char *tmp;
	tmp = pMemArea;

	for (int i = 0; i < size; i++)
	{
		*tmp = 0;
		tmp++;
	}

	for (int i=0; i < size; i++)
	{
		*pMemArea = read();
		pMemArea++;
	}
	return READ_OK;
}
int UART::getDataToMemAreaUntil(unsigned char *pMemArea, unsigned char ch)
{
	unsigned char *tmp;
	tmp = pMemArea;
	int cnt = 0;

	while (*tmp != ch)
	{
		*pMemArea = read();
		tmp = pMemArea;
		pMemArea++;
		cnt++;
	}
	return cnt;
}


char UART::write(char cwinp)
{
	return -1;
}


