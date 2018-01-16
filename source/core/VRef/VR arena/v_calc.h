//математика которая будет обрабатывать и наполнять руку данными



#ifndef _VCALC
#define _VCALC
#include "v_sys.h"
#include "v_output.h"
#include "v3d.h"
#include "VCCEL\dataframe.h"
//#include "ringbuff.h"
//#include <math.h>

//#define V3Di V3Df

#ifndef BYTE
#define BYTE  unsigned char
#endif

extern bool modeAxelGiro; // true - axel mode, false giro mode
//bool float::operator == (const loat & other);
int calcinit(void);
void calcrest();
//bool cmp(float f1,float f2);
void tobinb(BYTE inp);
void tobin(WORD inp);
//void c_send_data(V3Di ain,V3Di gin,unsigned int ts);
void c_send_data(MATCHFRAME in);




#endif