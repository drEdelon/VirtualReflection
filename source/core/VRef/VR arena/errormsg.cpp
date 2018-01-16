#include "errormsg.h"

int lastError=0;				//error message system feald


void printError()
{
	printf("ERROR %d \n",lastError);
	system("pause");
}