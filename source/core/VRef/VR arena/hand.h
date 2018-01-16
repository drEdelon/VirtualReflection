#ifndef _HAND
#define _HAND
#include "v3d.h"
//#include "v_calc.h"


extern V3Df handbone[5][4];

void drawHand();
//#include <windows.h>
//#include <gl\gl.h>
//
//#include "brush.h"
////tendon
////muscle
////bone | / \
////joint + *
///*
//
// |  |  |  |
// +  +  +  +
// |  |  |  |
// +  +  +  +   |
// |  |  |  |   +
// *  *  *  *  / 
//  \  \/  /  +
//   \ /  /  /  
//    /  /  *
//   /  /  
//
////*/
//#define JTYPE float
//#define FINGER_NUM 5
//#define PHALANX_NUM 3
//struct DDhand
//{
//	JTYPE joint [(FINGER_NUM)*(PHALANX_NUM+1)];
//	DV3Df palm;
//
//};
//struct SDhand
//{
//
//};
//
//// SD - static data - пропорции анатомии и степиней свободы
//// DD - dinamic data - снятые показания о положении и изгибе
//// делигация не обработаных усилий
//
//
//
//
//
//
//struct JOINT // крутящий момент, угол поворота, степень свободы.
//{
//	JTYPE maxbend;	//SD
//	JTYPE minbend;	//SD
//	JTYPE* curbend;	//DD
//	V3Df DOF;		//SD
//	float torque;	//DD
//
//	//JOINT();
//	//JOINT(JTYPE min, JTYPE max):maxbend(max), minbend(min), curbend((max+min)/2) {};
//	//void set(JTYPE cur);
//	//JTYPE get();
//	//void draw();
//};
//
//#define BOTYPE float
//struct BONE // габариты, форма, точка приложения усилия.
//{
//	BOTYPE lenght,diametr;	//SD
//};
//
//struct PHALANX // иерархия отображения и реакции на усилия.
//{
//	JOINT joint;
//	BONE bone;
//	JOINT* precursor;	
//	//PHALANX(): joint(0,90), lenght(1), diametr(0.5) {};
//	//PHALANX(PTYPE len, PTYPE di): joint(0,90), lenght(len), diametr(di){};
//	//PHALANX(PTYPE len, PTYPE di, JTYPE min, JTYPE max): joint(min, max), lenght(len), diametr(di){};
//	//void draw();
//};
//
//struct FINGER	// строение пальца и базовое размещение
//{
//	JOINT joint;
//	PHALANX phalanx[PHALANX_NUM];
//	V3Df bOffset;	//SD
//
//	//FINGER():joint(-15, 15){};
//	//FINGER(JTYPE min,JTYPE max):joint(min, max){};
//	//FINGER(JOINT jo):joint(jo){};
//	////FINGER(PHALANX pha):phalanx({pha,pha,pha}){};
//	//void draw();
//};
//
//#define PALM BRUSH // точка отсчета позиции и ориентации в пространстве, размер
////struct PALM
////{	
////	V3Df position;
////	V3Df orientation;
////	V3Df size;
////
////	PALM(): position(V3Df(0, 0, 0)), orientation(V3Df(0, 0, 0)), size(V3Df(1, 1, 0.5)){};
////	PALM(V3Df pos, V3Df orient, V3Df sz): position(pos), orientation(orient), size(sz){};
////	void draw();
////
////};
//
//struct HAND	// функциональное описания анатомии и физических свойств руки
//{
//	PALM palm;		//DD
//	FINGER finger[FINGER_NUM];
//
//	bool LRmode;	//SD
//
//	//HAND(bool lrm):LRmode(lrm){};
//	//void draw();
//};
//

#endif