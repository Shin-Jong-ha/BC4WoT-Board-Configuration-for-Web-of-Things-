#include "index.h"
#include <fcntl.h>

int initNumber[] = {32, 28, 34, 16, 36, 18, 20, 22, 26, 24, 42, 30};

void init()
{

	int i = 0, fp2;
	char fpData[30], gpioChar[39];

	for(i = 0 ; i < 13 ; i++)
	{
		sprintf(gpioChar, "%d", initNumber[i]);

		gpioExport(gpioChar);
		gpioDirection(gpioChar, "out");
		gpioDrive(gpioChar, "strong");	
		gpioValueWrite(gpioChar, "0");
	}
}