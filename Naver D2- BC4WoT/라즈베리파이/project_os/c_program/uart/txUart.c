#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int loopCounter = 0;

int txUart(int gpio_fd, int gpioNumber)
{
   
   int serialFd, fd ,fd1, fd2,num,j=0;
   int i = 0;
   char con_data[255];
   char data[255];
   char gpio_config_str[255];
   char uart[100];
   static char result[2];
   static char config[100];
   static char config_count[100];
   char dataTemp;
   char dataResult[100];
   int dataCondition = 0;   
   char testloop[6];
   int fd2Read;

   char test[10];

   char *gpioLocation = "/var/www/project_os/DB/gpio/1";
   char *pwd_config_temp   = "/var/www/project_os/DB/gpio_config_DB/";
   
   if ((serialFd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
   {
      printf("aabb");
      fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
      return 1;
   }
   else
	{
	   printf("success\n");
	}


   i = 0;

   fd2            = open(gpioLocation, O_RDONLY);
   fd2Read         = read(fd2, data, 255);
   data[fd2Read]   = '\0';

   close(fd2);

   i = 0;

   while(1)
   {
      if(dataCondition == 1)
      {
         if(data[i] == '=')// 마지막 문자일때
         {      
            printf("data : %s", dataResult);

            dataResult[i - 1] = '\0';
            write(serialFd,dataResult,strlen(dataResult));
            fflush(stdout);

            break;
         }

         dataResult[i - 1] = data[i];

         i++;


      }
      else
      {

         if(data[i] == '-')
         {
            printf("%c" , data[i]);
            i++;
            dataCondition = 1;
         }

      }
   }

   serialClose(serialFd);

   return 0;
}