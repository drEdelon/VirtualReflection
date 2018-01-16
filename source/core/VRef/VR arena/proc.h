// набор процедур для обработка виндовс сообщений


#ifndef _PROC
#define _PROC
#include "v_sys.h"

typedef void (*MSGUINT)(WPARAM	wParam,	LPARAM	lParam);

int findLastProc();
void procListInit();
int findIndexProc(UINT umsg);
int addMsgProc(UINT umsg, MSGUINT procp);
int callProc(UINT umsg, WPARAM wParam, LPARAM lParam);



#endif