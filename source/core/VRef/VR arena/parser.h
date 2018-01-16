#ifndef _MPARSER
#define _MPARSER

//#define QUAT_MODE

#define CHECK_OK 0
#define CRC_INCORRECT -1
#define PACKAGE_SIZE_INCORRECT -2

#include <iostream>
#include "circleBuffer.h"
#include "threadCBuff.h"
#include "Vccel\dataframe.h"
#include "errormsg.h"



struct PACKET_FORMAT
{
	unsigned char header[4];
	int crc;
	int data_length;
	unsigned char *mask_for_parse;
	unsigned char header_check;
};

#endif
