#ifndef _VINPUT
#define _VINPUT

#include "parser.h"
#include "testResistors.h"
#include "ringbuff.h"
#include "v_output.h"

//дефайны парсера
#define CRC_OFF 0
#define CRC_ON 1
#define SIZE_HEADER_AND_CRC 4
#define CHECK_NOT_OK -1
#define NOT_FIND_HEADER -1
#define NOT_FIND_HEADER_BUFFER_IS_FULL -3
#define FIND_HEADER_BUT_PACKET_IS_NOT_FULL -2

#define TYPE_OF_PACKET 1	// 0 - palm mode
							// 1 - mahony mode
							// 2 sphera mode
#define PALM_PACKET 0
#define QUAT_PACKET 1
#define SPHERE_PACKET 2
#define INTEGRAL_PACKET 3
#define VECTORS_PACKET 4
#define GLOVE_PACKET 5

// коэфициенты алгоритма махони
#define mpu6050_mahonysampleFreq 61.0f // sample frequency in Hz
#define mpu6050_mahonytwoKpDef (2.0f * 0.5f) // 2 * proportional gain
#define mpu6050_mahonytwoKiDef (2.0f * 0.1f) // 2 * integral gain

// калибровка акселерометра и гироскопа
#define MPU6050_AXOFFSET 0
#define MPU6050_AYOFFSET 0
#define MPU6050_AZOFFSET 0
#define MPU6050_AXGAIN 16384.0
#define MPU6050_AYGAIN 16384.0
#define MPU6050_AZGAIN 16384.0
#define MPU6050_GXOFFSET -42
#define MPU6050_GYOFFSET 9
#define MPU6050_GZOFFSET -29
#define MPU6050_GXGAIN 16.4
#define MPU6050_GYGAIN 16.4
#define MPU6050_GZGAIN 16.4

// дефайны потока
#define BUF_SIZE 255

// инклюды потока
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "comPort.h"
#include "circleBuffer.h"
#include "Vccel\dataframe.h"
#include "errormsg.h"

void testPotok();
void closePotok();

extern DWORD   dwThreadIdArray;
extern HANDLE  hThreadArray; 

extern unsigned char dataFromResistors[24];

short parse(void *tempval, int packet_id);
void threadOFF();




void inputrest();
void uartThreadON(void *parseArea);


#endif