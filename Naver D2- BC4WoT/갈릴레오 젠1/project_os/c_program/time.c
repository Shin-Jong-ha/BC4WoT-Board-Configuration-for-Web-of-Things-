#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
	*******************************************************************
	이코드는 리눅스의 시간를 나타내는 time을 이용하여 타이머를 구현한 코드이다.
	Time_DB의 값에는 Pin#, Timer#, 현재상태값 ex)3 10 0 이 입력이 되면 그 값을 읽어
	시간의 흐름에 따라서 Timer#을 줄여서 0이 되면 해당 Pin#의 상태를 제어할 수 있도록 구현하였다.
	*******************************************************************
*/

time_t   current_time;

struct tm *t;

int timer(void) //time_linux
{
	static int sec = 0;
	int secNext = 0,buffer = 0;
	char buf_data[255];
	char *Time_DB_PATH  = "/usr/local/apache/htdocs/project_os/DB/Time_DB/timer";	// web에서 입력한 값ex) 3 10 0--> 3번 핀에 10초 타이머 초기값은 0(on)
	int time_fd;
	char chr_string[13][3] = {0};			// 문자형 배열
	int i, j, k, l = 0;						
	char *ptr;								// 공백 단위로 Time_DB_PATH의 데이터를 읽어서 전달할 포인터
	char result[255];						// 결과값을 전달할 배열
	int cnt = 0;							// 배열 i의 값을 알기 위한 카운터
	char insertDatabase[255] = {0};
	char insertDatabaseTemp[10] = {0};
	/*
	   ***************************
	   1. secNext		- 현재 시간의 초를 나타낸다.
	   2. sec			- 전역 변수로써 이전 번 시간의 초를 나타낸다.
	   ***************************
	*/
	time( &current_time);

	t = gmtime(&current_time);
	secNext = t->tm_sec;
	printf("tm_sec => %d\n", t->tm_sec);

	if( secNext - sec != 0)					// 시간이 흘렀을 경우에
	{
		//기능 수행 : time_DB의 데이터를 읽어와서 
		//파일의 내용을 \n을 만날때 마다 처리 EOF를 만나기 전까지 무한 루프
		time_fd				= open(Time_DB_PATH, O_RDWR);
		buffer				= read(time_fd, buf_data, 255);
		close(time_fd);
		buf_data[buffer]	= '\0';		// buffer 값이 0 아니면 -1?

	//1. 문자형 배열에 핀 값을 대입		
		ptr	= strtok( buf_data, " " "\n");	// buf_data의 값을 공백 단위로 끊어서 ptr에 전달

		for( i = 0 ; ptr != NULL ; i++)
		{
			for( j = 0 ; j < 3 ; j++ )
			{
				chr_string[i][j] = atoi(ptr);		/// 배열에 ptr에 공백 단위로 전달된 값을 대입
				printf("chr_string[%d][%d] => %d\n", i, j, chr_string[i][j]);
				ptr = strtok(NULL, " " "\n");
			}
			cnt++;
		}
		
	//2. 타이머 값이 0 이상인 경우를 찾고 1씩 감소, 타이머 값이 0인 경우 값을 반전시키기
		for( i = 0 ; i < cnt ; i++)
		{
			chr_string[i][1] -= 1;	
			for( l = i ; l < cnt ; l++)			// 삭제 하고 뒤 배열을 당기기 위한 반복문
			{
				if( chr_string[i][1] == 0)		// 타이머가 0이 되면 동작을 반전
				{
					sprintf(insertDatabaseTemp, "%d", chr_string[i][2]); // insertDatabaseTemp에 임시로 저장한다.
					DBWrite(data_sprintf(i), insertDatabaseTemp);
					
					printf("Delete result = %d %d %d \n", chr_string[i][0], chr_string[i][1], chr_string[i][2]);
					// 타이머가 다 되었기 때문에 해당 액션을 취함

					// 0이 되면 이 배열에 그다음 배열 넣기 (삭제)
					k = i;
					for( ; k < cnt ; k++)
					{
						for( j = 0 ; j < 3 ; j++ )
						{
							chr_string[k][j] = chr_string[k+1][j];
						}
					}
					chr_string[i][1] -= 1;
					cnt--;
				}
			}
		}

		k = 0;

		time_fd				= open(Time_DB_PATH, O_WRONLY | O_TRUNC); // timer 파일을 파일 초기화 한채로 연다.

		for( i = 0 ; i < cnt ; i++)		// result 1차원 배열에 chr_string 2차원 배열 값 넣기
		{
			for( j = 0 ; j < 3 ; j++ )
			{
				sprintf(insertDatabaseTemp, "%d", chr_string[i][j]); // insertDatabaseTemp에 임시로 저장한다.

				if(i == 0 && j == 0){
					strcpy(insertDatabase, insertDatabaseTemp); // 처음 내용일 경우에 insertDatabase에 저장한다.
				}else{
	
					if(j != 0){ // 첫 번째 문단의 처음이 아닐 때 띄워쓰기를 저장하지 않는다.
						strcat(insertDatabase, " ");
					}
					strcat(insertDatabase, insertDatabaseTemp); // 문자를 계속 이어서 저장함.
				}
			}
			strcat(insertDatabase, "\n");
		}

		write( time_fd, insertDatabase, strlen(insertDatabase)); // 데이터베이스에 데이터를 입력한다.

		close(time_fd);
	}

	sec = secNext;
 
   return 0 ;
}

