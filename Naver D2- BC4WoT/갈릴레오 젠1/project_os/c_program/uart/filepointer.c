#include "index.h"
#include <fcntl.h>

// gpio 설정이 존재하는지 안하는지 확인하는거 추가함 (2015.08.12)

// gpio 설정이 존재하는지 안하는지 확인하는거 추가함 (2015.08.12)
// Galileo Gen1 만 period 1000000으로 생성하는거 추가함



/*
*******************************************************************
이 코드는 이번 프로젝트에서 만든 함수들 중에서 중복적으로 많이 사용되는
기능을 한곳으로 모아둔 코드이다. 이 함수들을 중심으로 모든 기능이 구현되고
심볼릭 링크를 생성하는 export, 입출력 방향을 설정하는 direction등 이 존재한다.
헤더파일에 선언하여 다른 c파일에서 활용할 수 있다.

현재 구현되어 있는 C파일에서 대표적으로 활용되는 함수 기능을 묶은 파일
*******************************************************************
*/


void pwmPeriodFunction(char* gpioNumber) // PWM의 Period를 설정하는 함수.
{
	int fp, result;
	char location[40];

	strcpy(location, "/sys/class/pwm/pwmchip0/pwm");// PWM을 위한 경로 by 리눅스
	strcat(location, gpioNumber);
	strcat(location, "/period"); //해당 PWM의 period의 경로

	if(access(location, F_OK) != -1)
	{
		perror("PeriodAccess");
	}

	if((fp = open(location, O_WRONLY)) == -1) // 파일 오픈 및 오류 체크/
	{
		perror(location);
		close(fp);
	}

	if((result = write(fp, "1000000", 8)) == -1)// 고정값을 입력한다.
	{
		perror("pwm export");
	}
	else
	{
		perror("pwm export success"); // 종료되지 않고 export 되었을때,
	}

	close(fp);//파일을 닫는다.
}

void pwmExportFunction(char* gpioNumber) //PWM을 Export 하여 심볼릭 링크를 생성하는 부분.
{

	int fp, result;
	char location[40];
	
	strcpy(location, "/sys/class/pwm/pwmchip0/pwm"); // sysfs기능을 활용하여 심볼릭링크로 파일을 사용자가 제어할 수 있도록한다.
	strcat(location, gpioNumber); //pwm 넘버

	if(access(location, F_OK) != -1)
	{//접근 확인
		return;
	}

	if((fp = open("/sys/class/pwm/pwmchip0/export", O_WRONLY)) == -1)
	{// 파일을 쓰기전용으로 연다.
		perror("pwmEXPORT ERROR");
		close(fp);

	}
	
	if((result = write(fp, gpioNumber, strlen(gpioNumber))) == -1)
	{
		perror("pwm export");
	}
	else
	{
		perror("pwm export success");
	}

	close(fp);
}

void pwmEnableFunction(char* gpioNumber, char* ONOFF)//PWM을 사용하기 위해 Enable하는 기능.
{
	int fp, fpRead, result;
	char temp[100];
	char inout[100];
	char readResult[2];
	
	strcpy(temp, "/sys/class/pwm/pwmchip0/pwm");
	strcat(temp, gpioNumber);
	strcat(temp, "/enable");
	
//	fpRead = open(temp, O_RDONLY);
	fp = open(temp, O_WRONLY);

#ifdef DEBUG_OPEN
	if(fp == -1)
	{
		perror("pwmENABLEFUNCTION : ");
		exit(0);
	}
#endif
//	
//	read(fpRead, readResult, 1);
//
//	if(strcmp(readResult, ONOFF) != -1)
//	{
//		return;
//	}
//	
	if((result = write(fp, ONOFF, strlen(ONOFF))) == -1)//ONOFF데이터를 쓰는 부분.
	{
		perror("enable FAIL");
	}
	else
	{
		perror("enable success");
	}

	close(fp);
}

void pwmDutyFunction(char* gpioNumber, char* duty) // PWM의 Duty를 정하는 부분. PWM의 속도를 제어할 수 있다.
{

	char temp[100];
	char inout[100];
	char readResult[100];
	int fp, fpRead, result;

	strcpy(temp, "/sys/class/pwm/pwmchip0/pwm"); // 파일 경로 복사
	strcat(temp, gpioNumber); // 파일 경로에 PWM 번호 붙이기
	strcat(temp, "/duty_cycle");// duty파일 경로 지정.

	//fpRead = open(temp, O_RDONLY);
	fp = open(temp, O_WRONLY);// 파일 열기
#ifdef DEBUG_OPEN
	if(fp == -1)
	{
		perror("pwmDutyFunction : ");
		exit(0);
	}
#endif
	//read(fpRead, readResult, 1);

	//if(strcmp(readResult, duty) != -1)
	//{
	//	return;
	//}

	if((result = write(fp, duty, strlen(duty))) == -1) // 입력된  duty를 저장한다.
	{
		perror("duty FAIL");
	}
	else
	{
		perror("duty success");
	}

	close(fp);
}


void gpioExport(char *gpioNumber) // 리눅스의 sysfs에서 gpio를 제어하기 위해서 export하여 심볼릭 링크를 생성한다.
{
		int fp, fpRead;
		char location[40];

		printf("\n**********gpioExport********** \n");

		strcpy(location, "/sys/class/gpio/export");// 경로 저장.
		strcat(location, gpioNumber); //해당 피일 경로

		fp = open("/sys/class/gpio/export", O_WRONLY);

		if(fp == -1)
		{
			perror("gpioExport : ");
//			exit(0);
		}

		write(fp, gpioNumber, strlen(gpioNumber));// 데이터를 입력한다.
		close(fp);
}

void gpioDirection(char *gpioNumber, char *inout)
{ //gpio의 방향을 설정해주는 함수로서 sysfs 에서 sys/class/gpio/gpio 
		int fp, fpRead, n;
		char fpData[100];
		char readResult[10];

		printf("\n**********gpioDirection********** \n");
		
		strcpy(fpData, "/sys/class/gpio/gpio");
		strcat(fpData, gpioNumber);
		strcat(fpData, "/direction");

		fp = open(fpData, O_WRONLY);

		if(fp == -1)
		{
			perror("gpioDirection : ");
			exit(0);
		}

		write(fp, inout, strlen(inout));//디지털 I/O의 In/Out을 설정한다.
		close(fp);
}

void gpioValueWrite(char *gpioNumber, char *value)
{//gpio의 출력입력을 설정하는 파일이다. value 파일에 1을 입력하면 출력, 0을 입력하면 입력을 받는다.
		int fp, fpRead, n;
		static char fpData[100];


		printf("\n**********gpioValueWrite********** \n");

		strcpy(fpData, "/sys/class/gpio/gpio");
		strcat(fpData, gpioNumber);
		strcat(fpData, "/value");
		
		printf("gpioNumber # : %s\n", gpioNumber);
		printf("gpioValueLocation  :  %s\n", fpData);
		printf("gpioValue  :  %s size = %d\n\n", value, strlen(value));
		
		fp = open(fpData, O_WRONLY);

		if(fp == -1)
		{
			perror("gpioValueWrite : ");
			exit(0);
		}

		write(fp, value, strlen(value));//현재 상태를 입력하는 부분이다.

		perror("fp : ");
		close(fp);

}

char* gpioValueRead(char *gpioNumber)
{//gpio의 출력입력을 설정하는 파일이다. value 파일에 1을 입력하면 출력, 0을 입력하면 입력을 받는다.
		int fp;
		char fpData[100];
		static char result[2];

		strcpy(fpData, "/sys/class/gpio/gpio");
		strcat(fpData, gpioNumber);
		strcat(fpData, "/value");
		fp = open(fpData, O_RDONLY);

#ifdef DEBUG_OPEN	
		if(fp == -1)
		{
			perror("gpioValueRead : ");
			exit(0);
		}
#endif
		read(fp, result, 1); //현재 상태를 읽어오는 부분이다.

		printf("\n\n result : %s\n\n", result);

		close(fp);

		return result;
}

void gpioDrive(char *gpioNumber, char *setting)
{//gen1,gen2의 경우 drive를 설정해줘야 한다.
		char fpData[100];
		int fp;

		strcpy(fpData, "/sys/class/gpio/gpio");
		strcat(fpData, gpioNumber);
		strcat(fpData, "/drive");

		fp = open(fpData, O_WRONLY);
#ifdef DEBUG_OPEN
		if(fp == -1)
		{
			perror("gpioDrive : ");
			exit(0);
		}
#endif
		write(fp, setting, 7);
		close(fp);
}

int gpioPair(char *gpioNumber, char *gpioPair)
{//페어 기능 함수 하나의 gpio를 제어할때, 다른 gpio 상태도 같이 바꾸는 기능을 제공한다.
		int readResult;
		int fp;
		char fpData[100];

		strcpy(fpData, "/usr/local/apache/htdocs/project_os/DB/gpio_pair/");
		strcat(fpData, gpioNumber);

		fp = open(fpData, O_RDONLY);
#ifdef DEBUG_OPEN
		if(fp == -1)
		{
			perror("gpioPair : ");
			exit(0);
		}
#endif
		readResult = read(fp, gpioPair, 3); //저장된 값을 읽어오는 역활을 한다.

		return readResult;
}

void DBWrite(char *gpioNumber, char *setting)
{//DB에 입력하는 함수.
		char	fpData[100];
		char	fpRead[100];
		int		fp, strResult;
		int		pinMap[14] = {11, 12, 61, 62, 6, 0, 1, 38, 40, 4, 10, 5, 15, 7};//위 핀배은 gen1의 것이다.

// GPIO DB 경로 복사
		strcpy(fpData, "/usr/local/apache/htdocs/project_os/DB/gpio/");
		strcat(fpData, gpioNumber);
		printf("fp : %s\n", fpData);
		
// GPIO DB 파일 열기
		fp					=	open(fpData, O_RDONLY);

// 100 바이트 만큼 읽어온다.
		strResult			=	read(fp, fpRead, 100);
		fpRead[strResult]	=	'\0';

		close(fp);

		printf("현재 DB 저장 값 : %s %s %d", fpRead, setting, strcmp(fpRead, setting));// 현재 상태를 DB에 저장한다.

// 현재 측정되는 값과 DB에 저장되는 값이 같으면 파일 입출력 하지 않는다.
		if(strcmp(fpRead, setting) != 0)
		{
			printf("SUCCESS!");

// 파일을 열 때 파일을 0으로 초기화 하고 연다.
			if((fp = open(fpData, O_WRONLY | O_TRUNC)) == -1)
			{
					perror("DBWRITE : ");
//					exit(0);
			}

			write(fp, setting, strlen(setting));
			close(fp);
		}
}

