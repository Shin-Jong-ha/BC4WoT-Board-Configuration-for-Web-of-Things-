#include "index.h"
#include <fcntl.h>

int pinMap[] = {11, 12, 61, 62, 6, 0, 1, 38, 40, 4, 10, 5, 15, 7, 48, 50, 52, 54, 56, 58};

void output_DB(int fp ,int gpioNumber)
{
		int		i = 0, readResult, fp2, resultNumber;
		char	data[255]; // read DB Data (ON / OFF)
		char	fpData[100];
		char	temp[100];
		char	gpioChar[10], gpio_pair[3];
		char	test[10] = "1";
		char	result[1];

		gpioVariable(gpioNumber);

		if(gpioCompare(fp, gpioNumber) == 1)  
		{
			printf("aawefpowjefpojwefopjwpfojpewfjpwofej");
			return;
		} 
		else
		{	
			printf("**********output DB********** \n");

// read DB
			printf("Current GPIO # : %d\n", gpioNumber);
			
			resultNumber		= read(fp, data, 255); // read
			data[resultNumber]	= '\0';
			printf("Current GPIO DATA :  %s\n", data);

	// read DB
			read(fp, data, 1); // read
			result[0]	= data[0];
			result[1]	= '\0';

			close(fp);

			if(result[0] == '1' )
			{
					printf("SUCCESS!!@!@!#\n\n");
			}
			else if(result[0] == '0' )
			{
					printf("fail!!!!!!!!!!\n\n");
			}

			readResult = gpioPair(data_sprintf(gpioNumber), gpio_pair);

			if(readResult != 3)
			{
				gpio_pair[readResult] = '\0';
			}
			close(fp2);

			printf("GPIO_PAIR ::::::::::: %s", gpio_pair);

			if(gpio_pair[0] == '0')
			{
				printf("**************************NOPAIR\n");
			}
			else if(gpio_pair[0] > 0)
			{
				printf("**************************SUCCESS\n");
				DBWrite(gpio_pair, result);
			}
// GPIO SEND		
			sprintf(gpioChar, "%d", pinMap[gpioNumber]);

			gpioExport(gpioChar);
			gpioDirection(gpioChar, "out");
			gpioValueWrite(gpioChar, data);
		}
}