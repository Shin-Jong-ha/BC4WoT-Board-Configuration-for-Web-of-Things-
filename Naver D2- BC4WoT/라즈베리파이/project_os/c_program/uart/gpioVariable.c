#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>


int gpioVariable(int gpio_number)
{
	DIR *dp;
	char config[5],config_count[100],frist_var[100];

	int fd,fd2,resultTotal,gpioTotal;
	struct dirent *dent;
	int i = 0,x,j,k = 0;
	char* Filelist[255];
	char files[255];
	char* p;
	char buf[50],num[50];

	char fpResult[100],gpioResult[100];
	char data[255];

	char test[100];
	char location[40];
	
	int buff = 0;

   //비교할 gpio의 데이터 값을 읽어오는 부분.

   strcpy(location,"/usr/local/apache/htdocs/project_os/DB/gpio/");
   strcat(location,data_sprintf(gpio_number)); 

   fd2 = open(location,O_RDONLY);
   gpioTotal = read(fd2, gpioResult, 255);
   gpioResult[gpioTotal] = '\0';

   close(fd2);
   //

   printf("%s \n",gpioResult);

   sprintf(buf,"%d",gpio_number);

   if((dp = opendir("/usr/local/apache/htdocs/project_os/DB/gpio_variable")) == NULL)
   {
      printf("error");
//      exit(1);
   }

   while( (dent = readdir(dp)))
   {
      Filelist[i] = dent->d_name;
      printf("%s\n",dent->d_name);
   
      i++;
   }
   

   x = i;
   i = 0;
   printf("\n%s\n",buf);
   for( i = 0, j = 0; i < x; i++)
   {
      printf("Filelist %s\n",Filelist[i]);
      if((strstr(Filelist[i],buf)) != NULL )
      {
         num[j] = i;
         j++;
      }
      
   }
   printf("%d\n",j); // 변수.   //파일이름을 배열에 저장, 저장된 파일 이름을 비교, 파일의 번호를 넘버 배열에 저장, 
   x = j;

   for( j = 0; j < x; j++)
   {
      printf("Filelsit %s\n",Filelist[num[j]]);

      strcpy(files,"/usr/local/apache/htdocs/project_os/DB/gpio_variable/");
      strcat(files,Filelist[num[j]]);

      printf("%s\n",files);

      fd = open(files,O_RDONLY);

      resultTotal = read(fd, fpResult, 255);
      fpResult[resultTotal] = '\0';

      close(fd);

      printf("\n %s \n",fpResult);

      i = 0;
      while(1)
      {
         config[i++] = fpResult[k]; // 조건값 
      
         if(fpResult[k++] == ' ')
         {
            config[i] = '\0';
            printf("\n config %s \n",config);

			if(strcmp(config, "1000") != -1)
			{
				return;
			}

            break;   
         }
      }
       //비교 조건 ( == : 0, > : 1, >= : 2, < : 3, <= : 4)
      i = 0;

      while(1)
      {
         config_count[i++] = fpResult[k]; // 비교값이 입력된다.

         if(fpResult[k++] == ' ')
         {
            config_count[i] = '\0';
            printf("\n config_count %s \n",config_count);
            break;   
         }
      }

      i = 0;

      while(1)
      {
         frist_var[i++] = fpResult[k]; // 초기값

         if(fpResult[k++] == '\0')
         {
            printf("\n frist_var %s \n",frist_var);
            frist_var[i] = '\0';
            break;   
         }
      }
//      
      k = 0;
      resultTotal = 0;
      
      
      if(config[0] == '0')
      {
         printf("\n 같음 ");

         if(atoi(gpioResult) == atoi(config_count))
         {
            buff = atoi(frist_var) + 1;
            sprintf(frist_var,"%d",buff); // 다시 문자열로 바꾼다.
         }
      }
      else if(config[0] == '1')
      {
         if(atoi(gpioResult) > atoi(config_count))
         {
            printf("만세");
            buff = atoi(frist_var) + 1;
            sprintf(frist_var,"%d",buff); // 다시 문자열로 바꾼다.
         }
      }
      else if(config[0] == '2')
      {
         if(atoi(gpioResult) >= atoi(config_count))
         {
            printf("만세");
            buff = atoi(frist_var) + 1;
            sprintf(frist_var,"%d",buff); // 다시 문자열로 바꾼다.
         }
      }
      else if(config[0] == '3')
      {
         printf("\n 보다 작다 ");
         if(atoi(gpioResult) < atoi(config_count))
         {
            buff = atoi(frist_var) + 1;
            sprintf(frist_var,"%d",buff); // 다시 문자열로 바꾼다.
         }
      }
      else if(config[0] == '4')
      {
         
         printf("\n 작거나 같다 ");
         if(atoi(gpioResult) <= atoi(config_count))
         {
            printf("aaaa");
            buff = atoi(frist_var) + 1;
            sprintf(frist_var,"%d",buff); // 다시 문자열로 바꾼다.
         }
      }
      else
      {
         printf("\n 아무렇지도 않음 ");
      }
      //저장 되는 부분 문제 조건문 들어가는것은 이상무.
      printf("\n frist_var %s \n",frist_var);
      printf("\n config_count %s \n",config_count);
      printf("\n config %s \n",config);

      strcpy(test, config);
      strcat(test, config_count);
      strcat(test, frist_var);
      
      printf("%s\n", test);

      fd = open(files,O_WRONLY);
      write(fd,test,strlen(test));

      close(fd);

   }
   closedir(dp);
   return 0;
}