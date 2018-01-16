//модуль ответственный за работу на определенной платформе


#ifndef _VSYS
#define _VSYS


#include <windows.h>
#include <stdio.h>	
#include "errormsg.h"

#include "proc.h"

#define GET_X_LPARAM(lp)	((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)	((int)(short)HIWORD(lp))



extern bool appQuit;
extern int	wwidth, wheight;
extern bool	keys[256];
extern int	MxPos,MyPos;
extern short	MzDelta;
extern unsigned int mState;
extern short int	wxpos;
extern short int	wypos;
extern MSG	msg;


void wlpNOP(WPARAM	wParam,	LPARAM	lParam);
int sysinit(void);
int winmsgproc(void);
void sysrest(void);
#endif