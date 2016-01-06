#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>


#define def_hardware GALILEO
#define def_pin_number 20
#define def_seek 50

#define DEBUG_OPEN


char* data_sprintf(int data);

// gpiofilepointer

void gpioExport(char *gpioNumber);
void gpioDirection(char *gpioNumber, char *inout);
void gpioValueWrite(char *gpioNumber, char *value);
char *gpioValueRead(char *gpioNumber);
void gpioDrive(char *gpioNumber, char *setting);

void DBWrite(char *gpioNumber, char *setting);


// gpioCompare
int gpioCompare(int fp, int gpio_number);

int rxUart(int gpio_fd, char *gpioNumber);
int txUart(int gpio_fd, char *gpioNumber);