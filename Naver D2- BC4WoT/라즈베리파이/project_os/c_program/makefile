# Makefile

CC = gcc
CFLAGS = 
OBJS = main.o insert_DB.o output_DB.o init.o filepointer.o rxUart.o wiringSerial.o txUart.o gpioCompare.o gpioVariable.o insertUart.o
LIBS = index.h

all : add

add :	$(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS) $(LIBS)

insertUart.o : 		insertUart.c
	$(CC) $(CFLAGS) -c insertUart.c

rxUart.o : rxUart.c
	$(CC) $(CFLAGS) -c rxUart.c

gpioCompare.o : gpioCompare.c
	$(CC) $(CFLAGS) -c gpioCompare.c

gpioVariable.o : gpioVariable.c
	$(CC) $(CFLAGS) -c gpioVariable.c

txUart.o : txUart.c
	$(CC) $(CFLAGS) -c txUart.c

wiringSerial.o : wiringSerial.c
	$(CC) $(CFLAGS) -c wiringSerial.c

filepointer.o :		filepointer.c
	$(CC) $(CFLAGS) -c filepointer.c

init.o :		init.c
	$(CC) $(CFLAGS) -c init.c
	
main.o : 		main.c
	$(CC) $(CFALGS) -c main.c

insert_DB.o : 	insert_DB.c
	$(CC) $(CFLAGS) -c insert_DB.c

output_DB.o :	output_DB.c
	$(CC) $(CFLAGS) -c output_DB.c

clean :
	rm -f $(OBJS) add core
