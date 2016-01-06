#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main( void )
{
	int pid;
	int i, status = 0;

	i = 1000;
		pid = fork();		
	while(1)
	{
//		if(status == 0)
//		{
		
			if(pid == -1 )
			{
				perror("fork error");
				exit(0);
			}

			else if( pid == 0 )
			{
					while(1)
				{
					status = 1;
					printf("                          Childss : PID = %d\n", getpid());

						printf("-->%d\n", i);
						i++;
//						sleep(1);	
				}


				
			}
			
			else
			{
				printf("----------------------Parent : Child PID = %d\n", pid);
			}
//		}
	}
}
