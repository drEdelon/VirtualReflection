//#ifndef _TYPE_OF_STRUCTS
//
//#define _TYPE_OF_STRUCTS
////#pragma pack(show)
//#pragma pack(push,1)
////#pragma pack(show)
////PACK PUSH 1 
////typedef 
//struct MPUFRAME // 7x2 14b
//{
//	short ax, ay, az, termC, gx, gy, gz;
//
//};
// 
////typedef 
//struct MATCHFRAME //14 + 4   18b
//{
//	MPUFRAME mp;
//	unsigned long timestmp;
//};
//
////typedef 
//struct UARTFRAME // 4+18   22b
//{
//	char hd1, hd2, hd3, src;
//	MATCHFRAME ma;
//};
//
////typedef 
//union UUART // 22b
//{
//UARTFRAME uf;
//unsigned char data[sizeof(UARTFRAME)];
//};
//
//struct FINGERS
//{
//	unsigned short joint[20];
//};
//
//struct FFRAME
//{
//	char hd1, hd2, hd3, src;
//	FINGERS finger;
//};
//
//union FUART // 44b
//{
//	FFRAME ff;
//	unsigned char data[sizeof(FFRAME)];
//};
//
//struct TYPEOFDATA
//{
//	short offset;
//	short type;
//	TYPEOFDATA():offset(0), type(0) {}
//};
//
//
//
//
//
//
////#pragma pack(show)
//#pragma pack(pop)
////#pragma pack(show)
////#pragma PACK POP
//#endif