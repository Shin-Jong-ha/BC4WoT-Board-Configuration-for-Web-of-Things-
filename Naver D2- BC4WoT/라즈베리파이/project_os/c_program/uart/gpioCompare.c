#include "index.h"
#include <unistd.h>
#include <fcntl.h>

#define DEBUG

void insertCompare(char *index, char *gpioNumber)
{
	char result[5];
	
	strcpy(result, gpioNumber);
	result[strlen(gpioNumber) - 1] = '\0';

	DBWrite(result, index);
}

int gpioCompare(int fp, int gpio_number)
{
	char		compare[255];
	char		compareIndex[255];
	char		compareResult[255];
	char		gpioData[255];
	char		gpioLocation[100];
	char		fpCompareLocation[255]; // compare DB 주소가 저장된다.
	char		fpResult[100];
	char		compareNumber[255];

	int			fpCompare, resultTotal, counter = 0, i = 0, j = 0;
	int			fpResultSize;

// 현재 gpio_compare 복사한다.
	strcpy(fpCompareLocation, "/usr/local/apache/htdocs/project_os/DB/gpio_compare/");
	strcat(fpCompareLocation, data_sprintf(gpio_number));

	printf("\n***********gpioCompare**************\n");
	printf("fpCompareLocation : %s", fpCompareLocation);

	//exit(0);

	fpCompare	=  open(fpCompareLocation, O_RDONLY, S_IRUSR);

// open 오류가 있을 경우
	if ( fpCompare == -1 )
	{
		perror("open : fpCompare");
		close(fpCompare);
		
		return 0;
	}

// gpio_compare에서 255바이트 만큼 값을 읽어옴. ( gpio compare번호, 조건, 값 )
	resultTotal = read(fpCompare, fpResult, 100);
	fpResult[resultTotal] = '\0';

#ifdef DEBUG
	printf("--------------------fpResult\n%s", fpResult);
#endif
	close(fpCompare);

// 길이가 2보다 작을 경우, DB에 잘 못 저장되었다고 판단
	if(strlen(fpResult) < 5)
	{
		printf("DB Compare Error\n");
		return 0;
	}
	else
	{

// 조건이 여러개 있을 경우 반복해서 조건 데이터를 가져온다.
		while(1)
		{
			i = 0;

			// gpio 번호
			while(1)
			{
				compareNumber[i++] = fpResult[j];
			
				if(fpResult[j++] == ' ')
				{
					compareNumber[i] = '\0';
#ifdef DEBUG
					printf("\n1. compareNumber %s\n", compareNumber);
#endif
					break;	
				}
			}
			// 비교 조건 ( == : 0, > : 1, >= : 2, < : 3, <= : 4)
			i = 0;
			while(1)
			{
				compare[i++] = fpResult[j]; // 비교 조건 값이 입력된다.

				if(fpResult[j++] == ' ')
				{
					compare[i] = '\0';
#ifdef DEBUG
					printf("3. compareNumber %s \t Memory : %u \n", compareNumber, compareNumber);
					printf("4. compareNumber %s \n", compareNumber);
#endif
					break;	
				}
			}
			i = 0;
			while(1)
			{
				gpioData[i++] = fpResult[j]; // 비교 조건 값이 입력된다.

				if(fpResult[j++] == ' ')
				{
					gpioData[i - 1] = '\0';
#ifdef DEBUG
					printf("3. compareNumber %s \t Memory : %u \n", compareNumber, compareNumber);
					printf("4. compareNumber %s \n", compareNumber);
#endif
					break;	
				}
			}
			i = 0;
			// 비교 값

			while(1)
			{

#ifdef DEBUG
				printf("6. compare %s \n", compare);
#endif

				compareIndex[i++]	=	fpResult[j++];

				if(fpResult[j] == '\n' | fpResult[j] == '\0')
				{
					printf("success\n");
					compareIndex[i] = '\0';

#ifdef DEBUG3
					printf("HI!!\n");
					printf("6. compareIndex %s\n", compareIndex);
#endif			

	// GPIO DB 주소를 복사한다. GPIO 값과 compareIndex 값과 비교하기 위함
					strcpy(gpioLocation, "/usr/local/apache/htdocs/project_os/DB/gpio/");
					strcat(gpioLocation, data_sprintf(gpio_number));

	// 복사한 주소를 오픈함.
					fpCompare = open(gpioLocation, O_RDONLY, S_IRUSR);

					if(fpCompare == -1)
					{
						perror("fpCompare : ");
//						exit(0);
					}

	// 복사한 주소에서 100 바이트만큼 읽어온다.
					if((resultTotal = read(fpCompare, compareResult, 20)) == -1)
					{
						perror("resultTotal : ");
					}
					compareResult[resultTotal] = '\0';

					printf("\n\n현재 값 : %s", compareResult);
					close(fpCompare);

					if(compare[0] == '0')
					{
						printf("\n 같음 \n");
						printf("compareResult = %s \t compareIndex = %s", compareResult, compareIndex);

						if(atoi(compareResult) == atoi(compareIndex))
						{
							printf("\n gpioData : %c, compareNumber : %s\n", gpioData[0], compareNumber);
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					}
					else if(compare[0] == '1')
					{
						if(atoi(compareResult) > atoi(compareIndex))
						{
							printf("만세");
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					}
					else if(compare[0] == '2')
					{
						if(atoi(compareResult) >= atoi(compareIndex))
						{
							printf("만세");
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					}
					else if(compare[0] == '3')
					{
						printf("\n 보다 작다 ");
						if(atoi(compareResult) < atoi(compareIndex))
						{
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					}
					else if(compare[0] == '4')
					{
						
						printf("\n 작거나 같다 ");
						if(atoi(compareResult) <= atoi(compareIndex))
						{
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					}
					else
					{
						printf("\n 아무렇지도 않음 ");
					}

					if(fpResult[j] == '\0')
					{
						close(fpCompare);
						return;
					}
					if(fpResult[j] == '\n')
					{
						j++;
					}
					close(fpCompare);
					break;	
				}
			}
		}
	}

	
	return 1;
}