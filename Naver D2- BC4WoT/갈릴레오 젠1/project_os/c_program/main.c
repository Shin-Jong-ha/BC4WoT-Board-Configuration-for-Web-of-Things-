#include "index.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/*
*******************************************************************
 컨트롤 프로그램의 메인 부분으로 GPIO 설정 파일을 읽어오고 설정된 형태에 맞춰서
 동작하도록 함수를 호출한다. 호출된 함수는 각각의 C코드 파일로 분할하여 작성 하였다.
 각각의 코드 상단에 주석으로 설명을 추가 하였다.

 메인 부분의 기본 동작은 while문으로 loop를 통해서 핀 숫자 1 ~ 14, 또는 1 ~ 20 까지 등 
 루프문으로 동작한다. 
*******************************************************************
*/


char* data_sprintf(int number)
{
		static char data[100];
		
		sprintf(data, "%d", number);

		return data;
}

void analogRead(int fp, int gpioNumber)
{
		char	fpData[100];
		char	analogInt[][2] = {"0", "1", "2", "3", "4", "5"};
		int		fp2, readResult;
		char	result[10];

		if(gpioCompare(fp, gpioNumber) == 1)
		{
			write(0, "aawefpowjefpojwefopjwpfojpewfjpwofej", 5);
			return;
		}
		else
		{
			printf("wofeijwoeifjwioefj");
		}

		strcpy(fpData, "/sys/bus/iio/devices/iio:device0/in_voltage");
		strcat(fpData, analogInt[gpioNumber - 14]);
		strcat(fpData, "_raw");

		fp2 = open(fpData, O_RDONLY);

		if(fp2 == -1)
		{
			perror("readResult (Main) : ");
			//exit(0);
		}

		readResult = read(fp2, result, 255);

		result[readResult] = '\0';
		
		printf("\n\n --------------------------------------------------------------%d ::::::: %s\n\n", gpioNumber, result);

		DBWrite(data_sprintf(gpioNumber), result);
		
		close(fp2);
}

int main(void)
{
		int status = 0;
		// 파일 디스크립터
		int gpio_file, gpio_config_file, gpio_unexport, gpio_pair;
		
		// 자식 프로세스
		int pid, childPid, childPidTemp;

		// GPIO 읽어오기 위한 임시 변수
		int i = 0;
		int temp = 0;
		
		// GPIO 번호 
		int gpio_number = -1, gpio_config_number = -1;

		// DB로 부터 읽어온 값 저장
		
		char gpio_config_str[255] = {0};
		char gpio_result_str[2]; // DB에서 읽어온 값을 저장한다.
		char gpio_value_str[40];

		// DB 경로
		char *pwd_temp			= "/usr/local/apache/htdocs/project_os/DB/gpio";
		char *pwd_config_temp	= "/usr/local/apache/htdocs/project_os/DB/gpio_config_DB/";
		char *pwd_value_temp	= "/sys/class/gpio/gpio";

		char pwd[50] = {0};

		char* test[3] = {"nohup",  "/usr/local/apache/htdocs/project_os/c_program/uart/uart", "&"};

		/*
		   저수준 파일 입출력 구현

		   웹에서 GPIO 먼저 설정하면

		   **************************************************
		   1. gpio_DB.txt : GPIO에서 읽어오는 값을 데이터베이스에 저장함.
		   2. gpio_config_DB.txt : GPIO를 입력으로 할지 출력으로 할지 정한다. (웹에서 설정하고 C프로그램에서 읽는다.)
		   **************************************************
	    */

		init(); // Galileo Level Shifter 초기화
		pid = fork(); // 유아트 자식 프로세스 생성

		while(gpio_config_number++ < 19)
		{
				// 설정 DB 파일 오픈
				strcpy(gpio_config_str, pwd_config_temp);
				strcat(gpio_config_str, data_sprintf(gpio_config_number));

				gpio_config_file = open(gpio_config_str, O_RDONLY, S_IRUSR); // O_RDONLY, S_IRUSR

				if( gpio_config_file == -1 ) // DB 여는데 오류가 있을 경우 프로그램 처음으로 돌아감
				{
						perror("config_file error (MAIN)");
						close(gpio_config_file);

						continue; // 처음으로
				}

				read(gpio_config_file, gpio_result_str, 2); // GPIO 설정 값을 읽어온다.

				gpio_number++; // 몇번 GPIO인지

				/*
				   ***************************
				   1. HTML 입력 (HTML상으로 버튼) - 값을 읽어서 GPIO로 보내주어야함
				   2. 디지털 입력 - 외부 버튼 입력 : DB에 저장함
				   3. 디지털 출력 - DB값을 읽어서 출력한다. (HIGH / LOW)
				   4. 아날로그 입력 - 아날로그 값을 읽어서 DB에 저장함
				   5. 아날로그 출력 - DB값을 읽어서 출력함
				   ***************************
				*/

				// GPIO 데이터를 저장하거나 읽어오기 위한 부분
				strcpy(pwd, pwd_temp); // 경로 (/project_os/DB/gpio/) 를 복사함
				strcat(pwd, "/");
				strcat(pwd, data_sprintf(gpio_config_number)); // GPIO번호를 붙인다.
		
				if((gpio_file = open(pwd, O_RDWR, S_IRUSR)) == -1) // GPIO DB 파일을 연다.
				{
						perror("open_gpio_file (MAIN)");
						continue;
				}

				/* 
					output_DB(int data) : DB에 저장된 값을 읽어온다.
					insert_DB(int data) : DB에 값을 삽입한다.
				*/

				printf("\n\n --------------------------------------------------------------%d %c\n\n", gpio_config_number, gpio_result_str[0]);

//				if(status == 0)
//				{
//							pid = fork(); // 유아트 자식 프로세스 생성
//							printf("weofjoewjfoweijfoiwejf   %d\\n\n\n", pid);
//				}
//				
				timer();
				switch( gpio_result_str[0] )
				{
						case '0' : // 사용하지 않는 경우
								printf("사용하지 않음\n");
								break;
						case '1' : // 디지털 출력
								output_DB(gpio_file, gpio_config_number);
								break;
						case '2' : // 디지털 입력
								insert_DB(gpio_file, gpio_config_number); // 10000 대신에 GPIO에서 읽어오는 값으로 변경하기
								break;
						case '3' : // 아날로그 입력
								analogRead(gpio_file, gpio_config_number);
								break;
						case '4' : // PWM 출력
								analogOutput(gpio_file, gpio_config_number);
								break;
						case '5' : // Rx_insert. 

									if( pid == -1 )
									{
										perror("fork error");
									}
									else if( pid == 0 )
									{
										
	//									//Rx_rasb(gpio_file, gpio_config_number);
										childPid = getpid();
										status = 1;

	//										insertUart();
										if(execlp(test[1], test[1], (char *)NULL) == 0)
										{
											perror("execlp");
											exit(0);
										}
									}
									else
									{
										printf("wefoijweojfeoiw pid = %d, %d", childPid,pid);
									}

								
								break;
						case '6' :

									if( pid == -1 )
									{
										perror("fork error");
									}
									else if( pid == 0 )
									{
	//									//Rx_rasb(gpio_file, gpio_config_number);
	//										printf("pid = %d", pid);
											status = 1;
	//										insertUart();
										if(execlp(test[1], test[1], (char *)NULL) == 0)
										{
											perror("execlp");
											exit(0);
										}
	//									

									}
									else
									{
										printf("wefoijweojfeoiw pid = %d", pid);
	//										break;
									}

								break;
						default : // 예외 처리
								printf("오류\n");
								break;
				}

				close(gpio_file);
				close(gpio_config_file);
		
				i = 0; // 초기화
				gpio_number = -1;

				if(gpio_config_number == 19)
				{
					gpio_config_number = -1;
				}
		}
}
