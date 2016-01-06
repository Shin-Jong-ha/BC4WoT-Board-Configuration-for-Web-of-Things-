#include "index.h"
#include <fcntl.h>

int initNumber[] = {32, 28, 34, 16, 36, 18, 20, 22, 26, 24, 42, 30, 55};

void init() // 갈릴레오 보드에서 활용되는 init -> level shift를 위한 기능이다.
{
	int i = 0, fp2;
	char fpData[30], gpioChar[39];

	for(i = 0 ; i < 14 ; i++)
	{
		sprintf(gpioChar, "%d", initNumber[i]);

		gpioExport(gpioChar);
		gpioDirection(gpioChar, "out");
		gpioDrive(gpioChar, "strong");	

		if(initNumber[i] == 30)
		{
			gpioValueWrite(gpioChar, "0");
		}
		else if(initNumber[i] == 32)
		{
			gpioValueWrite(gpioChar, "1");
		}
		else
		{
			gpioValueWrite(gpioChar, "1");
		}
	}
}