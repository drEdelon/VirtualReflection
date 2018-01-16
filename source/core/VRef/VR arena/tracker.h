#ifndef _TRACKER
#define _TRACKER

#include "ringbuff.h"

struct TRACKER
{
	//RBUFFT<DV3Df,204800> track;//
	RBUFFT<DV3Df,200> track;//
};


#endif 