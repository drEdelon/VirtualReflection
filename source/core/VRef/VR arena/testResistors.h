#ifndef _TESTRESISTORS
#define _TESTRESISTORS
#include "errormsg.h"
#include "comPort.h"
extern UART ResMass;

int getDataComForRes(unsigned char &dataFromResistors, int sizeOfMemArea);


#endif