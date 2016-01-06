#include "index.h"
#include <fcntl.h>

// gpio 설정이 존재하는지 안하는지 확인하는거 추가함 (2015.08.12)

void gpioExport(char *gpioNumber)
{
      int fp;
      char location[40];

      strcpy(location, "/sys/class/gpio/export");
      strcat(location, gpioNumber);

      fp = open("/sys/class/gpio/export", O_WRONLY);
#ifdef DEBUG_OPEN
      if(fp == -1)
      {
         perror("gpioExport : ");
         exit(0);
      }
#endif
      write(fp, gpioNumber, 3);
      close(fp);
}

void gpioDirection(char *gpioNumber, char *inout)
{
      int fp;
      char fpData[100];
      char readResult[10];
      
      strcpy(fpData, "/sys/class/gpio/gpio");
      strcat(fpData, gpioNumber);
      strcat(fpData, "/direction");
//
//      fpRead = open(fpData, O_RDONLY);
//      n = read(fpRead, readResult, 10);
//      readResult[n] = '\0';
//
//      if(strcmp(readResult, inout) != -1)
//      {
//            return;
//      }

      fp = open(fpData, O_WRONLY);
#ifdef DEBUG_OPEN
      if(fp == -1)
      {
         perror("gpioDirection : ");
         exit(0);
      }
#endif
      write(fp, inout, 4);
      close(fp);
}

void gpioValueWrite(char *gpioNumber, char *value)
{
      int fp;
      static char fpData[100];
      char readResult[10];

      strcpy(fpData, "/sys/class/gpio/gpio");
      strcat(fpData, gpioNumber);
      strcat(fpData, "/value");
      
      printf("fpData ======== %s\n\n", fpData);
      printf("value ========= %s\n\n", value);
      fp = open(fpData, O_WRONLY);
#ifdef DEBUG_OPEN
      if(fp == -1)
      {
         perror("gpioValueWrite : ");
         exit(0);
      }
#endif
      write(fp, value, 3);
      close(fp);
}

char* gpioValueRead(char *gpioNumber)
{
      int fp;
      char fpData[100];
      static char result[2];

      strcpy(fpData, "/sys/class/gpio/gpio");
      strcat(fpData, gpioNumber);
      strcat(fpData, "/value");
      fp = open(fpData, O_RDONLY);

#ifdef DEBUG_OPEN   
      if(fp == -1)
      {
         perror("gpioValueRead : ");
         exit(0);
      }
#endif
      read(fp, result, 255);

      printf("\n\n result : %s\n\n", result);

      close(fp);

      return result;
}

void gpioDrive(char *gpioNumber, char *setting)
{
      char fpData[100];
      int fp;

      strcpy(fpData, "/sys/class/gpio/gpio");
      strcat(fpData, gpioNumber);
      strcat(fpData, "/drive");

      fp = open(fpData, O_WRONLY);
#ifdef DEBUG_OPEN
      if(fp == -1)
      {
         perror("gpioDrive : ");
         exit(0);
      }
#endif
      write(fp, setting, 7);
      close(fp);
}

int gpioPair(char *gpioNumber, char *gpioPair)
{
      int readResult;
      int fp;
      char fpData[100];

      strcpy(fpData, "/var/www/project_os/DB/gpio_pair/");
      strcat(fpData, gpioNumber);

      fp = open(fpData, O_RDONLY);
#ifdef DEBUG_OPEN
      if(fp == -1)
      {
         perror("gpioPair : ");
         exit(0);
      }
#endif
      readResult = read(fp, gpioPair, 3);
		close(fp);
      return readResult;
}

void DBWrite(char *gpioNumber, char *setting)
{
      char fpData[100];
      int fp;
      int result;

      result = atoi(gpioNumber);
      strcpy(fpData, "/var/www/project_os/DB/gpio/");
      strcat(fpData, gpioNumber);

      printf("%s\n", fpData );

      if((fp = open(fpData, O_WRONLY | O_TRUNC)) == -1)
      {
            perror("DBWRITE : ");
			close(fp);
            //exit(0);
      }
      write(fp, setting, strlen(setting));
      close(fp);
}
