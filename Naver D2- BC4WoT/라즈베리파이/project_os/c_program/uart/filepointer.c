#include "index.h"
#include <fcntl.h>

// gpio 설정이 존재하는지 안하는지 확인하는거 추가함 (2015.08.12)

// gpio 설정이 존재하는지 안하는지 확인하는거 추가함 (2015.08.12)
// Galileo Gen1 만 period 1000000으로 생성하는거 추가함

char* data_sprintf(int number)
{
		static char data[100];
		
		sprintf(data, "%d", number);

		return data;
}


void pwmPeriodFunction(char* gpioNumber)
{
	int fp, result;
	char location[40];

	strcpy(location, "/sys/class/pwm/pwmchip0/pwm");
	strcat(location, gpioNumber);
	strcat(location, "/period");

	if(access(location, F_OK) != -1)
	{
		perror("PeriodAccess");
	}

	if((fp = open(location, O_WRONLY)) == -1)
	{
		perror(location);
		close(fp);
	}

	
	if((result = write(fp, "1000000", 8)) == -1)
	{
		perror("pwm export");
	}
	else
	{
		perror("pwm export success");
	}

	close(fp);
}
void pwmExportFunction(char* gpioNumber)
{

	int fp, result;
	char location[40];
	
	strcpy(location, "/sys/class/pwm/pwmchip0/pwm");
	strcat(location, gpioNumber);

	if(access(location, F_OK) != -1)
	{
		return;
	}

	if((fp = open("/sys/class/pwm/pwmchip0/export", O_WRONLY)) == -1)
	{
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

void pwmEnableFunction(char* gpioNumber, char* ONOFF)
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
//		exit(0);
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
	if((result = write(fp, ONOFF, strlen(ONOFF))) == -1)
	{
		perror("enable FAIL");
	}
	else
	{
		perror("enable success");
	}

	close(fp);
}

void pwmDutyFunction(char* gpioNumber, char* duty)
{

	char temp[100];
	char inout[100];
	char readResult[100];
	int fp, fpRead, result;

	strcpy(temp, "/sys/class/pwm/pwmchip0/pwm");
	strcat(temp, gpioNumber);
	strcat(temp, "/duty_cycle");

	//fpRead = open(temp, O_RDONLY);
	fp = open(temp, O_WRONLY);
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

	if((result = write(fp, duty, strlen(duty))) == -1)
	{
		perror("duty FAIL");
	}
	else
	{
		perror("duty success");
	}

	close(fp);
}


void gpioExport(char *gpioNumber)
{
		int fp, fpRead;
		char location[40];

		printf("\n**********gpioExport********** \n");

		strcpy(location, "/sys/class/gpio/export");
		strcat(location, gpioNumber);

		fp = open("/sys/class/gpio/export", O_WRONLY);

		if(fp == -1)
		{
			perror("gpioExport : ");
//			exit(0);
		}

		write(fp, gpioNumber, strlen(gpioNumber));
		close(fp);
}

void gpioDirection(char *gpioNumber, char *inout)
{
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
//			exit(0);
		}

		write(fp, inout, strlen(inout));
		close(fp);
}

void gpioValueWrite(char *gpioNumber, char *value)
{
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
//			exit(0);
		}

		write(fp, value, strlen(value));

		perror("fp : ");
		close(fp);

}

char* gpioValueRead(char *gpioNumber)
{
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
//			exit(0);
		}
#endif
		read(fp, result, 1);

		printf("\n\n result : %s\n\n", result);

		close(fp);

		return result;
}

void gpioDrive(char *gpioNumber, char *setting)
{
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
//			exit(0);
		}
#endif
		write(fp, setting, 7);
		close(fp);
}

int gpioPair(char *gpioNumber, char *gpioPair)
{
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
//			exit(0);
		}
#endif
		readResult = read(fp, gpioPair, 3);

		return readResult;
}

void DBWrite(char *gpioNumber, char *setting)
{
		char	fpData[100];
		char	fpRead[100];
		int		fp, strResult;
		int		pinMap[14] = {11, 12, 61, 62, 6, 0, 1, 38, 40, 4, 10, 5, 15, 7};

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

		printf("현재 DB 저장 값 : %s %s %d", fpRead, setting, strcmp(fpRead, setting));

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

