//// module_IN.cpp : Defines the entry point for the console application.
////
//
//
//
//
//#include "module_IN.h"
//#define PALM_DATA 1
//#define FINGERS_DATA 2
//
//MATCHFRAME Palm;
//FINGERS Fingers;
//PARSER ParserOfInputData;
//TYPEOFDATA TempBuffForData;
//
//unsigned char dataFromResistors[8] = {0};
//
//void inputrest()
//{
//	threadOFF();
////	glovePort.close();
////	testPotok();
////	closePotok();
//}
//
//
//void parsePalm(void *tempval)
//{
//	
//	ParserOfInputData.lockOn();
//	
//	while(ParserOfInputData.inputBuff.readAllow == 0){}
//			
//	UARTFRAME tBase;
//	TYPEOFDATA test;
//
//	int cntI = 1;
//	short sizeForDel = ParserOfInputData.circToTemp(TempBuffForData, tempval);
//	tBase = *((UARTFRAME*)(ParserOfInputData.tempBuff)); 
//
//	ParserOfInputData.inputBuff.del(TempBuffForData.offset + sizeForDel);
//	ParserOfInputData.testerCBuff[1].offset = (-1);
//	
//	ParserOfInputData.lockOff();
//	
////	return tBase.ma;
//}
//void parseFingers(void *tempval)
//{
//	ParserOfInputData.lockOn();
//	
//	while(ParserOfInputData.inputBuff.readAllow == 0){}
//			
//	FFRAME tBase;
//	TYPEOFDATA test;
//
//	int cntI = 1;
//	short sizeForDel = ParserOfInputData.circToTemp(TempBuffForData, tempval);
//	tBase = *((FFRAME*)(ParserOfInputData.tempBuff)); 
//
//	ParserOfInputData.inputBuff.del(TempBuffForData.offset + sizeForDel);
//	ParserOfInputData.testerCBuff[1].offset = (-1);
//	
//	ParserOfInputData.lockOff();
//	
////	return tBase.finger;
//}
//TYPEOFDATA lookingData(short type)
//{
//	return ParserOfInputData.knockKnock(type);
//}
//int inputinit(void)
//{
//	ParserOfInputData.init();
//
//	return 0;
//}
//
//void threadOFF() // завершает поток ответственный за чтение из ком-порта
//{
//	ParserOfInputData.inputBuff.threadON = 0;	
//}
//
//
//short parse(void *tempval, short type)
//{
//	if (tempval == NULL) return POINTING_TO_ZERO;
//	TempBuffForData = lookingData(type);
//	if (TempBuffForData.offset == (-1)) 
//		return NO_DATA_IN_CIRCLE_BUFFER;
//	switch (type)
//	{
//		case 1:
//			parsePalm(tempval);
//		break;
//
//		case 2:
//			parseFingers(tempval);
//		break;
//
//	}
//	return READ_OK;
//}
//
//
//
////int main(int argc, CHAR* argv[])
////{
////	inputinit();
////	while(1)
////	{
////		TempBuffForData = lookingData(1);		// здесь то что в скобках отвечает за тип работы 0 - все 1 - ладонь 2 - пальцы.
////
////		if (TempBuffForData.offset != -1)
////		{
////			switch(TempBuffForData.type)
////			{
////			case 1:
////				Palm = parsePalm();
////				if (Palm.timestmp != 0)
////				if (TempBuffForData.type == 1)
////					std::cout	<< Palm.mp.ax << "     " 
////							<< Palm.mp.ay << "     " 
////							<< Palm.mp.az << "     " 
////				<< std::endl;
////	
////
////				break;
////			case 2:
////				Fingers = parseFingers();
////				if (TempBuffForData.type == 2)std::cout	<< Fingers.joint[0] << "     "
////							<< Fingers.joint[1] << "     " 
////							<< Fingers.joint[2] << "     " 
////							<< Fingers.joint[3] << "     " 
////							<< Fingers.joint[4] 
////				<< std::endl;
////				break;
////			}
////		
////		}
////		
////	/*	Palm = ParserOfInputData.parse();
////		if (Palm.timestmp != 0)
////		std::cout << Palm.mp.ax << "     " << Palm.mp.ay << "     " << Palm.mp.az << "     " << std::endl;
////	*/
////	}
////
////	return 0;
////}
//
