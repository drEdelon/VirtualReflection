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
	
	int state;							// ������ � ���� ��������� �������������
	int mode;							// ����� ������ (0-����������, 1-�����������)
	LPCTSTR sPortName;					// ����� ��� �����
	HANDLE hSerial;						// ��������� �� �������� ����������(COM-����)
	OVERLAPPED overlapped;				// ��� ������������ ������
	
	UART(int _mode);
	UART(LPCTSTR portNumber, int _mode);

	int init();					// �������������� ������������� com-���������� � ����������� �� ���������� ������ (mode)
	int init_async();			// ������������� ��� ����������� ������
	int init_sync();			// ������������� ��� ���������� ������
	void close();				// �������� com-����������
	void test();				// ��������
	char read();				// �������������� ����� ������ �� com-����� � ����������� �� ���������� ������ (mode)
	char read_sync();			// ������ ������� ��� ���������� ������
	char read_async();			// ������ ������� ��� ����������� ������
	int getDataToMemAreaUntil(unsigned char *pMemArea, unsigned char ch);	// ����� � �������� ����� (*pMemArea) �� ��� ��� ���� �� �������� �������� ������ (ch), ���������� ���������� ��������� ���������
	int getDataToMemArea(unsigned char *pMemArea, int size);				// ����� � �������� ����� (*pMemArea) �������� ���������� �������� (size)
	char write(char cwinp);		// ��������
	
	~UART();
};


#endif