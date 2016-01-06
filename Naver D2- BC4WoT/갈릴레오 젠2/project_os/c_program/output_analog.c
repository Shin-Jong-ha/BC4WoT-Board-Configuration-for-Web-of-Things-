#include "index.h"
#include <fcntl.h>

int Number[]		= {3, 5, 6, 9, 11, 10};
int pwmNumber[]		= {1, 3, 5, 7, 9, 11};
int pwmShifter[]	= {16, 18, 20, 22, 24, 26};
int pwmPullup[]		= {17, 19, 21, 23, 25, 27};
int pwmMux[]		= {64, 66, 68, 70, 72, 74};

void analogOutput(int fp, int gpioNumber)
{
		int		fp2, findIndex = 0;
		int		readResult;
		char	data[50]; // read DB Data (ON / OFF)
		char	fpData[100];
		char	temp[100];
		char	gpioChar[10];
		char	test[10] = "1";
		char	result[1];



		for(findIndex = 0 ; findIndex < 6 ; findIndex++)
		{
				if(Number[findIndex] == gpioNumber)
				{
						printf("\n\n------------- gpioNumber = %d\n\n", gpioNumber);
						
						gpioExport(data_sprintf(pwmShifter[findIndex]));
						gpioDirection(data_sprintf(pwmShifter[findIndex]), "out");
						gpioExport(data_sprintf(pwmPullup[findIndex]));
						gpioDirection(data_sprintf(pwmPullup[findIndex]), "in");
						gpioExport(data_sprintf(pwmMux[findIndex]));
						gpioValueWrite(data_sprintf(pwmMux[findIndex]), "1");

						// read DB
						readResult = read(fp, data, 50); // read
						data[readResult] = '\0';
						printf("\n\n---------------------------------data : %s\n\n", data);


						// GPIO SEND		
						pwmExportFunction(data_sprintf(pwmNumber[findIndex]));
						pwmEnableFunction(data_sprintf(pwmNumber[findIndex]), "1");
						pwmDutyFunction(data_sprintf(pwmNumber[findIndex]), data);
						
						close(fp);
						break;
				}
		}

		if(gpioCompare(fp, gpioNumber) == 1)
		{
			write(1, "aawefpowjefpojwefopjwpfojpewfjpwofej", 5);
			return;
		}


}