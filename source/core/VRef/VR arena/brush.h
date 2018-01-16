// отвечает за отрисовку объекта с паматью о его перемещении на заданное время

#ifndef _BRUSH
#define _BRUSH
#include <windows.h>
#include <gl\gl.h>	
#include <gl\glu.h>	
#include "v3d.h"
#include "tracker.h"
//#include "myGL.h"
//проверка
struct BRUSH
{	
	V3Df tra,rot,sz,min,max;
	bool bdraw;
	bool record;
	GLuint  GLBrush;
	TRACKER rec;
	
	BRUSH::BRUSH();
	
	void recordStart();
	void recordStop();
	DV3Df getFrame(WORD fr);
	

	void setB(float x,float y,float z,float rx,float ry,float rz);
	void setB(V3Df pos,V3Df rot);
	void setB(DV3Df inp);
	
	void setPos(float x,float y,float z);
	void setPos(V3Df inp);
	
	void move(float x,float y,float z);
	void move(V3Df inp);
	
	void setRot(float x,float y,float z);
	void setRot(V3Df inp);
	
	void setSiz(float x,float y,float z);
	void setSiz(V3Df inp);
	
	
	void initBrush(void);
	void store(V3Df ipos,V3Df irot);
	void store(DV3Df inp);

	void rangefix(float insize);
	void rangefix(V3Df in);
	void rangefix(V3Df inmin,V3Df inmax);
	void tracking(void);
	void draw(void);
};

#endif 