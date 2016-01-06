#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int loopCounter = 0;

int txUart(int gpio_fd, int gpioNumber)
{
   
   int serialFd, fd ,fd1, fd2,num,j=0;
   int i = 0;
   char data[255],con_data[255];
   char gpio_config_str[255];
   char gpioLocation[255]; // DB에서 읽어온 값을 저장한다.
   char uart[100];
   static char result[2];
   static char config[100];
   static char config_count[100];
   char dataTemp;
   char dataResult[100];
   int dataCondition = 0;   
   char testloop[6];
   int fd2Read;

   char *Gpio = "/var/www/project_os/DB/gpio/";
   char *pwd_config_temp   = "/var/www/project_os/DB/gpio_config_DB/";
   
   gpioExport("4");
   gpioExport("40");
   gpioExport("41");

   gpioDirection("4", "out");
   gpioDirection("40", "out");
   gpioDirection("41", "out");

   gpioValueWrite("4", "1");
   gpioValueWrite("40", "0");
   gpioValueWrite("41", "0"); // 

   if ((serialFd = serialOpen ("/dev/ttyS0", 9600)) < 0)
   {
      printf("aabb");
      fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
      return 1;
   }
   else
   {
      printf("aa");
   }

   if(loopCounter == 0)
   {
      printf("aa");
      /////////////// 환경 파일 읽기///////////////////
      strcpy(gpio_config_str,pwd_config_temp);
      strcat(gpio_config_str,gpioNumber);

      fd1 = open(gpio_config_str,O_RDONLY);
      num = read(fd1, con_data, 255); //파일 전체를 읽어온다.
      con_data[num] = '\0';
      close(fd1);

      printf("\n con_data %s \n",con_data);
      //////////////////////////////////////////

      i = 0;
      while(1)
      {
         config[i++] = con_data[j];
      
         if(con_data[j++] == ' ')
         {
            config[i] = '\0';
            printf("\n config %s \n",config);
            break;   
         }
      }
// 비교 조건 ( == : 0, > : 1, >= : 2, < : 3, <= : 4)
      i = 0;

      while(1)
      {
         config_count[i++] = con_data[j]; // 비교 조건 값이 입력된다.

         if(con_data[j++] == '\0')
         {
            config_count[i] = '\0';
            printf("\n config_count %s \n",config_count);
            break;   
         }
      }

      printf("\n %s \n",con_data);
      printf("\n %c \n",config[0]);
      printf("\n %d \n",atoi(config_count));
   }

   i = 0;

   sprintf(testloop, "%d", loopCounter);
   
   printf("testloop %s", testloop);
   printf("config_count %s", config_count);

   if( loopCounter > atoi(config_count))
   {
      fd1 = open(gpio_config_str,O_WRONLY);
      write(fd1,"0",1);
      close(fd1);

      printf("\n\nloopCounter : %d", loopCounter);

      loopCounter = 0;
      return;
   }

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
            loopCounter++;
            dataResult[i] = '\0';
            write(fd,dataResult,strlen(dataResult));
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
         else
         {
            break;
         }

      }
   }

   serialClose(fd);

   return 0;
}