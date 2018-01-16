#ifndef _DATAFRAME
#define _DATAFRAME

//#pragma pack(show)
#pragma pack(push,1)


struct MPUFRAME // 7x2 14b
{
	short ax, ay, az, termC, gx, gy, gz;
};
 
struct MATCHFRAME //14 + 4   18b
{
	MPUFRAME mp;
	unsigned long timestmp;
};

struct UARTFRAME // 4+18   22b
{
	char hd1, hd2, hd3, src;
	MATCHFRAME ma;
};

union UUART // 22b
{
	UARTFRAME uf;
	unsigned char data[sizeof(UARTFRAME)];
};

struct FINGERS
{
	unsigned short joint[20];
};

struct FFRAME
{
	char hd1, hd2, hd3, src;
	FINGERS finger;
};

union FUART // 22b
{
	FFRAME ff;
	unsigned char data[sizeof(FFRAME)];
};

struct TYPEOFDATA
{
	short offset;
	short type;
	TYPEOFDATA():offset(0), type(0) {}
};

struct QUAT_AND_ANGLES
{
	float qw, qx, qy, qz, roll, pitch, yaw;
};
union U_QUAT
{
	QUAT_AND_ANGLES q_a;
	char mass[28];
};

struct QUAT_ANGLES_GYRO_AXEL_TIME
{
	float qw, qx, qy, qz, roll, pitch, yaw, gx, gy, gz, ax, ay, az, timestamp;
};

struct GLOVE
{
  //unsigned char hd1, hd2, hd3, crc;
  unsigned char finger[25];
  float pos[3];
  float rot[3];
};

struct GLOVE_FULL
{
  unsigned char hd1, hd2, hd3, crc;
  unsigned char finger[25];
  float pos[3];
  float rot[3];
};

union U_PACK
{
  GLOVE_FULL glove_full;
  unsigned char buf[53];
};

#pragma pack(pop)


#endif