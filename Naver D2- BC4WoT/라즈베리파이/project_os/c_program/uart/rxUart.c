#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int rxUart(int gpio_fd, int gpioNumber)
{
   static int loopCounter = 0;
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
   int dataCondition = 0, m = 0;

   char *pwd_config_temp   = "/var/www/project_os/DB/gpio_config_DB/";

   if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
{
      fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
      return 1;
   }

   //gpioValueWrite("32", "1");

   if(loopCounter != 0)
   {
      /////////////// 환경 파일 읽기///////////////////
      strcpy(gpio_config_str,pwd_config_temp);
      strcat(gpio_config_str, data_sprintf(gpioNumber));

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
   }
   
   char *Gpio = "/var/www/project_os/DB/gpio/";
   strcpy(gpioLocation,Gpio);
   strcat(gpioLocation, data_sprintf(gpioNumber));
   
   i = 0;

   while(1)
   {
//      printf("m : %d\n", m++);
      dataTemp = (char)serialGetchar(fd);
      
      printf("dataTemp %c", dataTemp);
      if((int)dataTemp == -1)
      {
         break;
      }

      if(dataCondition == 1)
      {
         if(dataTemp == '=')// 마지막 문자일때
         {
            if((fd2 = open(gpioLocation, O_WRONLY | O_TRUNC)) == -1)
			 {
				perror("open");
				exit(0);
			 }
            data[i] = '\0';
            
            printf("data : %s gpioNumber : %d", data, gpioNumber);
            write(fd2,data,strlen(data));
            close(fd2);   

            break;
         }
         else
         {
            data[i] = dataTemp;
         }

         sprintf(uart,"\nPC > RPi = %c \n",(char)data[i]);
         write(1,uart,strlen(uart));
         fflush(stdout);
         i++;
      }

      if(dataTemp == '-')
      {
         dataCondition = 1;
      }      
   }
   serialClose(fd);

   if(gpioCompare(gpio_fd, gpioNumber) == 1)
   {
      printf("aawefpowjefpojwefopjwpfojpewfjpwofej");
   //   exit(0);
   //   return;
   }

   return 0 ;
}