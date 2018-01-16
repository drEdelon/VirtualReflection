//#include "threadCBuff.h"
//
//
//DWORD   dwThreadIdArray[MAX_THREADS];
//HANDLE  hThreadArray[MAX_THREADS]; 
//
//UART glovePort;
//
//void testPotok()
//{
//	 WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
//}
//void closePotok()
//{
//	for(int i=0; i<MAX_THREADS; i++)
//    {
//        CloseHandle(hThreadArray[i]);
//    }
//}
//
//
//int potok(CBUFF *pInputBuff)
//{
//	for( int i=0; i<MAX_THREADS; i++ )
//    {
//		hThreadArray[i] = CreateThread( 
//        NULL,                   // default security attributes
//        0,                      // use default stack size  
//        threadFunction,       // thread function name
//        pInputBuff, //pDataArray[i],          // argument to thread function 
//        0,                      // use default creation flags 
//        &dwThreadIdArray[i]);   // returns the thread identifier 
//
//        if (hThreadArray[i] == NULL) 
//        {
//           ErrorHandler(TEXT("CreateThread"));
//           ExitProcess(3);
//        }
//    } // End of main thread creation loop.
//    return 0;
//}
//
//void bp(void)
//{
//	
//}
//
//DWORD WINAPI threadFunction( LPVOID lpParam ) 
//{ 
//	CBUFF *pInputBuff;
//	pInputBuff = (CBUFF*)lpParam;
//	
//	do
//	{
//		glovePort.state = glovePort.init();
//
//		while ((!glovePort.state) && (pInputBuff->threadON))
//		{
//			ReturnValue ReceiveData = glovePort.read();
//			if (ReceiveData.state)
//			{
//				while((pInputBuff->infill()) == (SIZE_OF_CIRCLE_BUFFER - 1) )
//				{
//					//bp();
//				}
//				while(pInputBuff->writeAllow == 0)
//				{}
//				pInputBuff->readAllow = 0;
//				pInputBuff->put(ReceiveData.sReceivedChar);
//				pInputBuff->readAllow = 1;
//	//			c_send_data(ParserOfInputData.parse());
//			}
//
//			else 
//			{
//				if (pInputBuff->takenPlaceBuff > sizeof(UARTFRAME))
//				{
//
//
//				}
//			
//			}
//		}
//	} while((glovePort.state) && (pInputBuff->threadON));
//	return 0; 
//}
//
//
//
//void ErrorHandler(LPTSTR lpszFunction) 
//{ 
//    // Retrieve the system error message for the last-error code.
//
//    LPVOID lpMsgBuf;
//    LPVOID lpDisplayBuf;
//    DWORD dw = GetLastError(); 
//
//    FormatMessage(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
//        FORMAT_MESSAGE_FROM_SYSTEM |
//        FORMAT_MESSAGE_IGNORE_INSERTS,
//        NULL,
//        dw,
//        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//        (LPTSTR) &lpMsgBuf,
//        0, NULL );
//
//    // Display the error message.
//
//    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
//        (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 
//    StringCchPrintf((LPTSTR)lpDisplayBuf, 
//        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
//        TEXT("%s failed with error %d: %s"), 
//        lpszFunction, dw, lpMsgBuf); 
//    MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK); 
//
//    // Free error-handling buffer allocations.
//
//    LocalFree(lpMsgBuf);
//    LocalFree(lpDisplayBuf);
//}
