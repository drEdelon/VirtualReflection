#include "winmsg.h"
#include "myGL.h"


										
void keydown(WPARAM	wParam,	LPARAM	lParam)
{
	keys[wParam] = TRUE;									
}

void keyup(WPARAM	wParam,	LPARAM	lParam)
{
	keys[wParam] = FALSE;									
}

void mousemove(WPARAM	wParam,	LPARAM	lParam)
{
	mState = wParam;
	MxPos = GET_X_LPARAM(lParam)-wwidth/2; 
	MyPos = GET_Y_LPARAM(lParam)-wheight/2; 
}

void mousewheel(WPARAM	wParam,	LPARAM	lParam)
{
	mState = GET_KEYSTATE_WPARAM(wParam);
	MzDelta = GET_WHEEL_DELTA_WPARAM(wParam)/120;
}


void wmove(WPARAM	wParam,	LPARAM	lParam)
{
	wxpos=LOWORD(lParam);
	wypos=HIWORD(lParam);
}

void wsize(WPARAM	wParam,	LPARAM	lParam)
{
	ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));	
}


void eventInit()		//наполняет массив указателей на функции (proc.cpp) нужными функциями
{
	addMsgProc(WM_KEYDOWN,keydown);
	addMsgProc(WM_KEYUP,keyup);
	addMsgProc(WM_MOUSEMOVE,mousemove);
	addMsgProc(WM_MOUSEWHEEL,mousewheel);
	addMsgProc(WM_MOVE,wmove);
	addMsgProc(WM_SIZE,wsize);
}


/*/
	switch (uMsg)													// Check For Windows Messages
	{
		case WM_QUIT:
			{
				printf("try to quit\n");
				//KillGLWindow();
				exit(1);
			}

		case WM_ACTIVATE:											// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))									// Check Minimization State
			{
				active=TRUE;										// Program Is Active
			}
			else
			{
				active=FALSE;										// Program Is No Longer Active
			}

			return 0;												// Return To The Message Loop
		}

		case WM_SYSCOMMAND:											// Intercept System Commands
		{
			switch (wParam)											// Check System Calls
			{
				case SC_SCREENSAVE:									// Screensaver Trying To Start?
				case SC_MONITORPOWER:								// Monitor Trying To Enter Powersave?
				return 0;											// Prevent From Happening
			}
			break;													// Exit
		}

		case WM_CLOSE:												// Did We Receive A Close Message?
		{
			PostQuitMessage(0);										// Send A Quit Message
			return 0;												// Jump Back
		}
		
		/*
		case WM_MOUSEWHEEL:
		{
			mState = GET_KEYSTATE_WPARAM(wParam);
			MzDelta = GET_WHEEL_DELTA_WPARAM(wParam)/120;
			//xPos = GET_X_LPARAM(lParam)-wwidth/2; 
			//yPos = GET_Y_LPARAM(lParam)-wheight/2; 
			return TRUE;
		}

		case WM_MOUSEMOVE:
		{
			mState = wParam;
			MxPos = GET_X_LPARAM(lParam)-wwidth/2; 
			MyPos = GET_Y_LPARAM(lParam)-wheight/2; 
			//SetCursorPos(wwidth/2, wheight/2);
			return 0;
		}//* /


		
		case WM_MOVE:
		{
			wxpos=LOWORD(lParam);
			wypos=HIWORD(lParam);
			//printf("x:%d y:%d  %d\n",(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),-1);
			return 0;
		}

		case WM_SIZE:												// Resize The OpenGL Window
		{
			//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));			// LoWord=Width, HiWord=Height
			return 0;												// Jump Back
		}
	
		/*case 127:	break;							
		case 32:	break;							
		case 132:	break;							
		case 160:	break;							//* /

		//default:printf("%d  \n",uMsg);
	}
	//*/