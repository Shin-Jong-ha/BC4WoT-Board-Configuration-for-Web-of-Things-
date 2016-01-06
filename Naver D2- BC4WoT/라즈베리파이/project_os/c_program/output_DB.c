#include "index.h"
#include <fcntl.h>

int RB_pinMap[27][27] = {{3,2},{5,3},{7,4},{8,14},{10,15},{11,17},{12,18},{13,27},{15,22},
		         {16,23},{18,24},{19,10},{21,9},{22,25},{23,11},{24,8},{26,7},
		         {29,5},{31,6},{32,12},{33,13},{35,19},{36,16},{37,26},{38,20},{40,21}};

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
			while(i < 26)
			{
				if(gpioNumber == RB_pinMap[i][0])
				{
					break;
				}
				else
				{
					i++;
				}
			}
							
			sprintf(gpioChar, "%d", RB_pinMap[i][1]);
			gpioExport(gpioChar);
			gpioDirection(gpioChar, "out");
			gpioValueWrite(gpioChar, result);
			i = 0;
		}

}