#ifndef _ERRORMSG
#define _ERRORMSG

#include <stdio.h>
#include <windows.h>

// ERROR MSG SECTION 0-1000
#define ERROR_OK 0
#define SOMETHING_WRONG 1

#define WINMSGPROC 50
#define NOWINMSGPROC 51


#define PROCLIST_IS_FULL 100

#define SIZE_OF_ACCEL_MATH_BUFF 204800

#define RINGBUFF_IS_FULL 300
#define RINGBUFF_IS_EMPTY 301
#define RINGBUFF_READ_IS_LOCKED 302
#define RINGBUFF_WRITE_IS_LOCKED 303

// INPUT ERROR SECTION 1000-1100
#define READ_OK 1000
#define READ_ERR 1001
#define PORT_NOT_EXIST 1150				//¬ыбранный вами порт не существует. ѕроверте правильно ли выбран порт.
#define PORT_NOT_OPEN 1151				//ѕорт не может быть открыт по какой-то причине.
#define GET_STATE_ERR 1152				//getting state error
#define SERIAL_PORT_STATE_ERR 1153		//error setting serial port state
#define SERIAL_PORT_TIMEOUTS_ERR 1154
#define CIRCLE_BUFF_FULL 1120
#define CIRCLE_BUFF_EMPTY 1121
#define READ_DATA_LESS_THEN_YOU_NEED 1122
#define NO_DATA_IN_CIRCLE_BUFFER 1180
#define POINTING_TO_ZERO 1181
#define BUFFER_IN_IS_FULL 1182
#define ERROR_WITH_PARSE_AREA 1183

#define OUT_OF_RANGE 600

// OUTPUT ERROR SECTION 1500-2000
// GL_MODE ERROR SECTION 1900-2000
#define CREATEGLWINDOW_FALSE 1900


extern int lastError;

void printError();



#endif





	//
	//procListInit();
	//addMsgProc(1,myproc1);
	//addMsgProc(2,myproc2);
	//callProc(3,0,0);
	//callProc(2,0,0);
	//parr[0]=myproc1;
	//parr[1]=myproc2;
	//parr[1]();
	//parr[0]();
	//*parr[0]=(int)myproc1;
	//pProc=myproc2;	
	//pProc();