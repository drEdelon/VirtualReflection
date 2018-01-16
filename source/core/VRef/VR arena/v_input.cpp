#include "v_input.h"
#include <iostream>


MATCHFRAME Palm;
FINGERS Fingers;
CBUFF inputBuff;

unsigned char palm_data[] =		{1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 14, 15, 16, 17}; 
unsigned char mahony_data[] =	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27}; 
unsigned char sphere_data[] =	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
//unsigned char graph_data[] =	{0, 1, 2, 3, 4, 5};
unsigned char graph_data[] =	{1, 0, 3, 2, 5, 4};
unsigned char vectors_data[] =	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35}; 
unsigned char glove_data[] =	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52}; 
unsigned char terminator_data = 0;

PACKET_FORMAT packet_format[] = {
									{ "hdp", CRC_ON, 18, palm_data, 0},
									{ "hdq", CRC_OFF, 28, mahony_data, 0},
									{ "hds", CRC_OFF, 12, sphere_data, 0},
									{ "hdg", CRC_OFF, 6, graph_data, 0},
									{ "hdv", CRC_OFF, 36, vectors_data, 0},
									{ "hdd", CRC_OFF, 53, glove_data, 0},
									{ "000", 0, 0, &terminator_data, 0}
								};

DWORD   dwThreadIdArray;
HANDLE  hThreadArray; 
UART glovePort(ASYNC_MODE);

U_QUAT quat_memarea;




int find_this_header(int type_of_packet)
{
	int infill_cbuff = inputBuff.infill();
	int header_cnt = 0;
	bool header_ok = false;

	for (int i = 0; i < infill_cbuff; i++)
	{
		if ((inputBuff.read(i) == packet_format[type_of_packet].header[0]) && ((infill_cbuff - i) > 3))
		{
			header_cnt = i;
			header_ok = true;

			for (int j = 0; j < 2; )
			{
				if (inputBuff.read(++header_cnt) == packet_format[type_of_packet].header[++j])continue;
				else 
				{
					header_ok = false;
					break;
				}
			}
			if (header_ok)
			{
				if(infill_cbuff - (i + SIZE_HEADER_AND_CRC) < packet_format[type_of_packet].data_length)return -2; 
				return i;
			}
		}
	}
	if (infill_cbuff > SIZE_OF_CIRCLE_BUFFER - packet_format[type_of_packet].data_length) return -3;
	return -1;
}
int check_this_data(int type_of_packet, int shift)
{

	if (packet_format[type_of_packet].crc != 0)
	{
		int temp_crc = 0;
		int shift_to_data = shift + SIZE_HEADER_AND_CRC;
		for (int i = shift_to_data; i < shift_to_data + packet_format[type_of_packet].data_length; i++)
		{
			temp_crc = (temp_crc ^ inputBuff.read(i));
		}
		if (temp_crc == inputBuff.read(shift_to_data - 1))return CHECK_OK;
		else 
		{
			std::cout << "CRC is incorrect" << std::endl;
			return CRC_INCORRECT;
		}
	}
	return CHECK_OK;

}
int parse_this_data(int type_of_packet, unsigned char *memarea, int shift)
{
		//while(parse_complete){}
	
	inputBuff.writeAllow = 0;	//lockOn();

	while(inputBuff.readAllow == 0){}

	for(int i = 0; i < packet_format[type_of_packet].data_length; i++)
	{
		//*(memarea + mask_for_parse[i]) = inputBuff.read(shift + size_of_header + crc + i);
		
		*(memarea + packet_format[type_of_packet].mask_for_parse[i]) = inputBuff.read(shift + SIZE_HEADER_AND_CRC + i);
		
	}
	inputBuff.writeAllow = 1; //lockOff();


	inputBuff.del(SIZE_HEADER_AND_CRC + packet_format[type_of_packet].data_length + shift);
	return CHECK_OK;
}


//********************
//
//
//********************
void inputrest()
{
	threadOFF();
//	glovePort.close();
//	testPotok();
//	closePotok();
}







void threadOFF() // завершает поток ответственный за чтение из ком-порта
{
	//ParserOfInputData.inputBuff.threadON = 0;	
	inputBuff.threadON = 0;
}




short parse(void *tempval, int packet_id)
{
	int shift = -1;
	int tmp;

	shift = find_this_header(packet_id);

	if (shift == NOT_FIND_HEADER)
	{
		std::cout << "Header not find. " << std::endl;
		return CHECK_NOT_OK;
	}

	if (shift == NOT_FIND_HEADER_BUFFER_IS_FULL)
	{
		std::cout << "Buffer is full. Header not find. " << std::endl;
		return CHECK_NOT_OK;
	}

	if (shift == FIND_HEADER_BUT_PACKET_IS_NOT_FULL)
	{
		std::cout << "Packet data not full. Need wait. " << std::endl;
		return CHECK_NOT_OK;
	}
	

	tmp = check_this_data(packet_id, shift);

	if (tmp == CRC_INCORRECT)
	{
		std::cout << "CRC is incorrect" << std::endl;
		inputBuff.del(SIZE_HEADER_AND_CRC + shift);
		return CHECK_NOT_OK;
	}
	tmp = parse_this_data(packet_id, (unsigned char*)tempval, shift);

	return READ_OK;
}




DWORD WINAPI threadFunction_sync( LPVOID lpParam ) 
{ 
	RBUFFT <MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF> *pInputBuff;
	//(RBUFFT<MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF>*)lpParam->init();
	pInputBuff = (RBUFFT<MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF> *)lpParam;
	

	do
	{
		glovePort.state = glovePort.init();

		while (!glovePort.state)
		{
			char ReceiveData = glovePort.read();
			//if (ReceiveData.state)
			//{
				//while((ParserOfInputData.inputBuff.takenPlaceBuff) == (SIZE_OF_CIRCLE_BUFFER - 1) )
				//{
				//	//bp();
				//}
				//while(ParserOfInputData.inputBuff.writeAllow == 0)
				while(inputBuff.writeAllow == 0)
				{}
				//ParserOfInputData.inputBuff.readAllow = 0;
				//ParserOfInputData.inputBuff.put(ReceiveData);
				//ParserOfInputData.inputBuff.readAllow = 1;
				inputBuff.readAllow = 0;
				inputBuff.put(ReceiveData);
				inputBuff.readAllow = 1;
	//			c_send_data(ParserOfInputData.parse());
			
				
			//}
			//else 
			//{
			//	if (ParserOfInputData.inputBuff.takenPlaceBuff > sizeof(UARTFRAME))
			//	{
			//		MATCHFRAME wwwTest;
			//		parse(&wwwTest, 0);
			//	}
			//}
		}
	} while(glovePort.state);
	return 0; 
}


DWORD WINAPI threadFunction_async( LPVOID lpParam ) 
{ 
	RBUFFT <MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF> *pInputBuff;
	//(RBUFFT<MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF>*)lpParam->init();
	pInputBuff = (RBUFFT<MATCHFRAME,SIZE_OF_ACCEL_MATH_BUFF> *)lpParam;
	
		COMSTAT comstat;
		unsigned char bufrd, ch;
		unsigned long  btr = 0, temp = 0, mask = 0, signal = 0;

	do
	{
		glovePort.state = glovePort.init();

		while (!glovePort.state)
		{
			glovePort.overlapped.hEvent = CreateEvent(NULL,TRUE,TRUE,NULL);
			SetCommMask(glovePort.hSerial,EV_RXCHAR);
			WaitCommEvent(glovePort.hSerial, &mask, &glovePort.overlapped);
			signal = WaitForSingleObject(glovePort.overlapped.hEvent, INFINITE);

			if(signal == WAIT_OBJECT_0) 
				{
					if(GetOverlappedResult(glovePort.hSerial, &glovePort.overlapped, &temp, true)) 
						if((mask & EV_RXCHAR)!=0)
						{
							 ClearCommError(glovePort.hSerial, &temp, &comstat);		//нужно заполнить структуру COMSTAT
							 btr = comstat.cbInQue;                          	//и получить из неё количество принятых байтов
							 if(btr)                         			//если действительно есть байты для чтения
							 {
								//while(ParserOfInputData.inputBuff.writeAllow == 0){}
								 while(inputBuff.writeAllow == 0){}
								//ParserOfInputData.inputBuff.readAllow = 0;
								inputBuff.readAllow = 0;
								for(int i = 0; i < btr; i++)
								{
									ch = glovePort.read();
									//ParserOfInputData.inputBuff.put(ch);
									inputBuff.put(ch);
									//ReadFile(hSerial, &bufrd, 1, &temp, &overlapped);  // получаем 1 байт

									
								}
								//ParserOfInputData.inputBuff.readAllow = 1;
								inputBuff.readAllow = 1;
							 }

						}
				}
		}
	} while(glovePort.state);
	return 0; 
}



void ErrorHandler(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK); 

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

void testPotok()
{
	// WaitForMultipleObjects(1, hThreadArray, TRUE, INFINITE);
}
void closePotok()
{
        CloseHandle(hThreadArray);
}




void uartThreadON_sync(void *parseArea)
{

		hThreadArray = CreateThread( 
        NULL,                   // default security attributes
        0,                      // use default stack size  
        threadFunction_sync,         //threadFunction_a,       // thread function name
        parseArea,              //pInputBuff, //pDataArray[i],          // argument to thread function 
        0,                      // use default creation flags 
        &dwThreadIdArray);      // returns the thread identifier 

        if (hThreadArray == NULL) 
        {
           ErrorHandler(TEXT("CreateThread"));
           ExitProcess(3);
        }
   // return 0;
}

void uartThreadON_async(void *parseArea)
{

	hThreadArray = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
    threadFunction_async,         //threadFunction_a,       // thread function name
    parseArea,              //pInputBuff, //pDataArray[i],          // argument to thread function 
    0,                      // use default creation flags 
    &dwThreadIdArray);      // returns the thread identifier 

    if (hThreadArray == NULL) 
    {
       ErrorHandler(TEXT("CreateThread"));
       ExitProcess(3);
    }
   // return 0;
}

void uartThreadON(void *parseArea)
{
	if(glovePort.mode == SYNC_MODE)  uartThreadON_sync(parseArea);
	else  uartThreadON_async(parseArea);
}


