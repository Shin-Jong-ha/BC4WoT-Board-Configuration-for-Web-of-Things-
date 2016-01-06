#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

extern int rxUart(int gpio_fd, int gpioNumber);
extern int txUart(int gpio_fd, int gpioNumber);

int insertUart(void)
{
	int			processId;
	int			status;
	int			fpConfig, fpReadIndex, i;
	char		data[255];
	char		location[50] = "/var/www/project_os/DB/gpio_config_DB/";
	char*		gpioFile[2] = {"/var/www/project_os/DB/gpio/8", "/var/www/project_os/DB/gpio/10"};
	
	processId = (int)getpid();
	while(1)
	{
		status = 0;

		for(i = 0 ; i < 2 ; i++)
		{
			if( i == 0)
			{
				strcat(location, data_sprintf(8));
			}
			if( i == 1)
			{
				strcat(location, data_sprintf(10));
			}
			fpConfig			= open(location, O_RDONLY);
			fpReadIndex			= read(fpConfig, data, 255);
			data[fpReadIndex]	= '\0';

			if( data == 7 || data == 8 )
			{
				status = (i + 1); // 0일때는 사용안함, 1일 때는 RX, 2일 때는 TX, 3일 때는 둘다 사용함
			}
		}

		if(status == 1)
		{
			rxUart(gpioFile[0], 0);
		}
		else if(status == 2)
		{
			txUart(gpioFile[1], 1);
		}
		else if(status == 3)
		{
			rxUart(gpioFile[0], 0);
			txUart(gpioFile[1], 1);
		}
		else
		{
			exit(0);
			//process종료
		}	
	}
}
