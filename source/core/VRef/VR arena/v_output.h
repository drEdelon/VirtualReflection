// модуль для вывода изображения
#ifndef _VOUTPUT
#define _VOUTPUT
#include "v_sys.h"
#include "ringbuff.h"
#include "brush.h"
#include "myGL.h"

extern float xobj;
extern float yobj;
extern float zobj;
extern float Cdist;
extern bool acel_draw;
extern bool giro_draw;
extern BRUSH brush;//,brush1;
extern bool folow;


extern char VisMode;
extern int cpoint;
extern V3Df visTri;
#define VIS_CUBE 0
#define VIS_GRAPH 1
#define VIS_HAND 2
#define VIS_QUAT 3
#define VIS_SPHERE 4
#define VIS_VECTORS 5


int outputinit(void);
int DrawGLScene(GLvoid);
void outputrest();
void vectors_infill(float *vec, int num);

//*

//*/

#endif