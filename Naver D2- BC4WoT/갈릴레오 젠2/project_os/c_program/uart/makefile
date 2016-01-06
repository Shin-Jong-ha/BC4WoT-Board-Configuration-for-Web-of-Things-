# Makefile

CC = gcc
CFLAGS = 
OBJS = filepointer.o rxUart.o wiringSerial.o txUart.o insertUart.o gpioCompare.o gpioVariable.o
LIBS = index.h

all : uart

uart :	$(OBJS)
	$(CC) $(CFLAGS) -o uart $(OBJS) $(LIBS)

gpioVariable.o :	gpioVariable.c
	$(CC) $(CFLAGS) -c gpioVariable.c

filepointer.o :		filepointer.c
	$(CC) $(CFLAGS) -c filepointer.c

insertUart.o : 		insertUart.c
	$(CC) $(CFALGS) -c insertUart.c

rxUart.o :		rxUart.c
	$(CC) $(CFLAGS) -c rxUart.c

txUart.o :		txUart.c
	$(CC) $(CFLAGS) -c txUart.c

wiringSerial.o :	wiringSerial.c
	$(CC) $(CFLAGS) -c wiringSerial.c

gpioCompare.o :		gpioCompare.c
	$(CC) $(CFLAGS) -c gpioCompare.c


clean :
	rm -f $(OBJS) uart core
