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

int main(void)
{
	int			status;
	int			fpConfig, fpReadIndex, i;
	char		data[2];
	char		location[50] = "/var/www/project_os/DB/gpio_config_DB/";
	char*		gpioFile[2] = {"/var/www/project_os/DB/gpio/10", "/var/www/project_os/DB/gpio/8"};
	
	while(1)
	{
		status = 0;

		for(i = 0 ; i < 2 ; i++)
		{
			if( i == 0 )
			{
				strcat(location, data_sprintf(10));
			}
			else
			{
				strcat(location, data_sprintf(8));
			}
			printf("location : %s\n", location);
			fpConfig			= open(location, O_RDONLY);

			if(fpConfig == -1)
			{
				perror("fpConfig");
			}
			fpReadIndex			= read(fpConfig, data, 1);
			
			data[fpReadIndex]	= '\0';

			if( data[0] == '3' || data[0] == '4')
			{
				status += (i + 1); // 0일때는 사용안함, 1일 때는 RX, 2일 때는 TX, 3일 때는 둘다 사용함
			}

			close(fpConfig);
			strcpy(location, "/var/www/project_os/DB/gpio_config_DB/");
		}
		printf("status = %d\n\n", status);

		if(status == 1)
		{
			printf("rx");
			rxUart(gpioFile[0], 0);
		}
		else if(status == 2)
		{
			write(1,"tx", 3);
			txUart(gpioFile[1], 1);
		}
		else if(status == 3)
		{
			printf("all");
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
