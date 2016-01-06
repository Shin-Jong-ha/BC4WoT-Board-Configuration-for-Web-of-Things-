 #include "index.h"
#include <unistd.h>
#include <fcntl.h>

void levelInit(int gpioNumber)
{
	char* GPIO[] = {"32", "28"};  
	int fp;

	if(gpioNumber == 0)
	{
		gpioValueWrite(GPIO[0], "0");
	}
	else if(gpioNumber == 0)
	{
		gpioValueWrite("45", "1");
	}
}
