#ifndef _CIRCLEBUFFER
#define _CIRCLEBUFFER

#include "errormsg.h"

#define SIZE_OF_CIRCLE_BUFFER 1000
#define uchar unsigned char

struct CBUFF
{
	uchar circBuff[SIZE_OF_CIRCLE_BUFFER];		// ������ ������ � ������
	int cntB, cntE;								// �������� ������ � ����� ������
	int takenPlaceBuff;							// ���������� ������ � ������
	bool readAllow, writeAllow;					// ������ �� ������ � ������
	bool threadON;								// ��������� ������ ������
	CBUFF::CBUFF();

	void beginMove(int step);					// ����������� ������ ������ �� �������� (step)
	void endMove(int step);						// ����������� ����� ������ �� �������� (step)
	int infill();								// ���������� �������� ������������ ������
	void del();									// ������� ������ ������� ������
	void del(int step);							// ������� step ������ ��������� ������
	void delete_all();							// ���������� �����
	uchar read();								// ���������� ������ ������� ������ �� ������ ���
	uchar read(int step);						// ���������� ������ + step ������� ������ �� ������ ���
	void put(uchar sReceivedChar);				// �������� ������� � ����� ������
	void forcePut(uchar sReceivedChar);			// �������� ������� � ����� ������, ���� ����� �������� - ���������� �� ����� ������� �������� 
	int address(WORD cur, WORD dest);			// ���������� ����� �������� (cur) �� ������� (dest). ��������� ��� ���������� "������"(����������� �������� ����� ������� ������)

};

#endif