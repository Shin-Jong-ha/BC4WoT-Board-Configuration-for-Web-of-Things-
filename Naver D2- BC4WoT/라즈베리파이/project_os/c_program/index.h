#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <wiringSerial.h>


#define def_hardware GALILEO
#define def_pin_number 20
#define def_seek 50

void insert_DB(int fp, int gpio_number);
void output_DB(int fp, int gpioNumber);

char* data_sprintf(int data);
void init(void);

// gpiofilepointer

void gpioExport(char *gpioNumber);
void gpioDirection(char *gpioNumber, char *inout);
void gpioValueWrite(char *gpioNumber, char *value);
char *gpioValueRead(char *gpioNumber);
void gpioDrive(char *gpioNumber, char *setting);
int gpioPair(char *gpioNumber, char *gpioPair);
void DBWrite(char *gpioNumber, char *setting);

int gpioVariable(int gpio_number);
int gpioCompare(int fp, int gpio_number);

int Rx_rasb(int gpio_fd, int gpioNumber);
int txUart(int gpio_fd, char *gpioNumber);