#include "v_sys.h"
#include "winmsg.h"


MSG	msg;

bool appQuit=false;				//ready to quit var
int	wwidth, wheight;
bool	keys[256];			//keyboard buffer 
int	MxPos,MyPos;
short	MzDelta;
unsigned int mState;
short int	wxpos=4;
short int	wypos=23;

bool	active=TRUE;	



int sysinit(void) // инициализация обработчика системных сообщений
{	
	procListInit();
	eventInit();
	return 0;
}

int winmsgproc()	//смотрит на наличие сообщений и обрабатывает их при наличии таковых
{	
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))					// Is There A Message Waiting?
	{
		//if (msg.message==WM_QUIT)								// Have We Received A Quit Message?
		//{	done=TRUE;	}										// If So done=TRUE
		//else													// If Not, Deal With Window Messages* /
		//{	appQuit=TRUE;printf("try to quit before %d\n",WM_QUIT);	}
		//else
		//{
			TranslateMessage(&msg);								// Translate The Message
			DispatchMessage(&msg);								// Dispatch The Message
		//}
		return WINMSGPROC;
	}
	return NOWINMSGPROC;
}

void sysrest(void){}

	//стандартный обработчик сообщений
LRESULT CALLBACK WndProc(	HWND	hWnd,					 		// Handle For This Window
							UINT	uMsg,							// Message For This Window
							WPARAM	wParam,							// Additional Message Information
							LPARAM	lParam)							// Additional Message Information
{

	if (callProc(uMsg,wParam,lParam)==ERROR_OK)
	{
		return 0;
	}
	else
	{	
		return DefWindowProc(hWnd,uMsg,wParam,lParam); // Pass All Unhandled Messages To DefWindowProc
	}
}