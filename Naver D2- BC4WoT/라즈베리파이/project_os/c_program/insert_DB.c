#include "index.h"
#include <fcntl.h>


extern int RB_pinMap[27][27];


void insert_DB(int fp, int gpio_number)
{	
	int fp2;
	char data[2]; // read DB Data (ON / OFF)
	char fpData[100];
	char temp[100];
	char gpioChar[10];
	char test[10] = "1";
	char result[3], gpio_pair[3];
	int i = 0, readResult;

// GPIO를 사용하겠다.
	
	while(i < 26)
	{
		if(gpio_number == RB_pinMap[i][0])
		{
			break;
		}
		else
		{
			i++;
		}
	}
			

	sprintf(gpioChar, "%d", RB_pinMap[i][1]);
	printf("\n\n %s \n",gpioChar);

	gpioExport(gpioChar);
	// fpData에 경로를 복사한다.
	gpioDirection(gpioChar, "in");

	// GPIO 형식 설정하기
//	gpioDrive(gpioChar, "strong");

	// GPIO 해당하는 값 확인하기

	// i가 0일 때, Level Shifter GPIO를 0으로 만들어준다.

	// 먼저 gpio_pair의 값을 읽어온다. 0일때는 사용하지 않음, 다른 값일때는 사용 (수정해야됨)

	readResult = gpioPair(data_sprintf(gpio_number), gpio_pair);

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
	}

// GPIO 값을 읽어옴. (버튼 누름 여부)

	printf("\n\nHello : %s %s \n\n", gpioValueRead(gpioChar),gpioChar);
	strcpy(result, gpioValueRead(gpioChar));

	DBWrite(data_sprintf(gpio_number), result);
	printf("result : %s", result);

// GPIO PAIR (짝) 값에 보낸다. (현재 13으로 고정) : 테스트 중

//	DBWrite(gpio_pair, result);

	if(result[0] == '0') // 버튼 안눌렀을때
	{
		printf("----------------------------------------off \n\n");

		DBWrite(gpio_pair, "0");
	}
	else // 눌렀을 때
	{
		printf("----------------------------------------ONsadsdasd \n\n");
		printf("%s aa\n" , result);

		DBWrite(gpio_pair, "1");
	}

}
