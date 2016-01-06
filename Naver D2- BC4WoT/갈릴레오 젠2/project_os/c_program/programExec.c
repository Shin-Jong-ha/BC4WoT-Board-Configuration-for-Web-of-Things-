#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	printf("aa");
//	pid_t pid;
//
//	if(strcmp(argv[1], "0") != -1)
//	{
//		switch(pid = fork()) 
//		{
//			case -1 :
//				perror("fork");
//				exit(1);
//				break;
//			case 0 :
//				printf("child process\n");
//				
//				if(execlp("/var/www/project_os/c_program/add", "/var/www/project_os/c_program/add", "&", (char *)NULL) == -1)
//				{
//					perror("execlp");
//					exit(1);
//				}
//				
//				exit(0);
//				break;
//			default :
//				printf(" parent process \n");
//				break;
//		}
//
//	}
//	else if(strcmp(argv[1], "1") != -1)
//	{
//		printf("DELETE\n");
//	}
}
