#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>


/*
*******************************************************************
이 코드는 uart를 자식 프로세스로 동작시키기 위해 만든 main 구문이다.
이 main문을 중심으로 uart 실행 파일이 생성되고, 메인 프로그램에서 호출할때, 자식프로세스로서 동작한다.

환경설정 파일에서 데이터를 읽고 해당 데이터가 송신인지 수신인지를 체크하여 동작하도록 하였다.
*******************************************************************
*/


extern int rxUart(int gpio_fd, int gpioNumber);
extern int txUart(int gpio_fd, int gpioNumber);

int main(void) // Uart 자식 프로세스의 메인 구문.
{
	int			status;
	int			fpConfig, fpReadIndex, i;
	char		data[2];
	char		location[50] = "/usr/local/apache/htdocs/project_os/DB/gpio_config_DB/";
	char*		gpioFile[2] = {"/usr/local/apache/htdocs/project_os/DB/gpio/0", "/usr/local/apache/htdocs/project_os/DB/gpio/1"};
	
	while(1)
	{
		status = 0; //rx,tx 사용을 체크한다.

		for(i = 0 ; i < 2 ; i++)
		{
			strcat(location, data_sprintf(i)); // gpio 설정 파일 경로
			printf("location : %s\n", location);
			fpConfig			= open(location, O_RDONLY);

			if(fpConfig == -1)
			{
				perror("fpConfig");
			}
			fpReadIndex			= read(fpConfig, data, 1);// 설정된 파일의 정보를 읽어온다.
			
			data[fpReadIndex]	= '\0';

			if( data[0] == '5' || data[0] == '6')
			{
				status += (i + 1); // 0일때는 사용안함, 1일 때는 RX, 2일 때는 TX, 3일 때는 둘다 사용함
			}

			close(fpConfig);
			strcpy(location, "/usr/local/apache/htdocs/project_os/DB/gpio_config_DB/");
		}
		printf("status = %d\n\n", status);

		if(status == 1)//rx만 사용하도록 설정되어 있는경우
		{
			printf("rx");
			rxUart(gpioFile[0], 0);
		}
		else if(status == 2)// tx만 사용하도록 설정되어 있는경우.
		{
			write(1,"tx", 3);
			txUart(gpioFile[1], 1);// tx함수.
		}
		else if(status == 3)// rx,tx를 둘다 사용하는 경우
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
