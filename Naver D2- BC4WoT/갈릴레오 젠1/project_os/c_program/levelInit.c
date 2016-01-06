#include "index.h"
#include <unistd.h>
#include <fcntl.h>

void levelInit(int gpioNumber)//갈릴레오 보드에서 level Shift를 하기 위해 초기화 하는부분.
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
	/*오류*/
}

