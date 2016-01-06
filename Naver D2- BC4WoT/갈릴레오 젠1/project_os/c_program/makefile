# Makefile

CC = gcc
CFLAGS = 
OBJS = main.o insert_DB.o output_DB.o init.o filepointer.o output_analog.o gpioCompare.o rxUart.o wiringSerial.o gpioVariable.o txUart.o levelInit.o insertUart.o time.o
LIBS = index.h

all : add

add :	$(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS) $(LIBS)

time.o :		time.c
	$(CC) $(CFLAGS) -c time.c

filepointer.o :		filepointer.c
	$(CC) $(CFLAGS) -c filepointer.c

init.o :		init.c
	$(CC) $(CFLAGS) -c init.c

main.o : 		main.c
	$(CC) $(CFALGS) -c main.c

insert_DB.o : 		insert_DB.c
	$(CC) $(CFLAGS) -c insert_DB.c

insertUart.o : 		insertUart.c
	$(CC) $(CFLAGS) -c insertUart.c

output_DB.o :		output_DB.c
	$(CC) $(CFLAGS) -c output_DB.c

output_analog.o :	output_analog.c
	$(CC) $(CFLAGS) -c output_analog.c

gpioCompare.o :		gpioCompare.c
	$(CC) $(CFLAGS) -c gpioCompare.c

rxUart.o :		rxUart.c
	$(CC) $(CFLAGS) -c rxUart.c

txUart.o :		txUart.c
	$(CC) $(CFLAGS) -c txUart.c


gpioVariable.o :	gpioVariable.c
	$(CC) $(CFLAGS) -c gpioVariable.c

wiringSerial.o :	wiringSerial.c
	$(CC) $(CFLAGS) -c wiringSerial.c

levelInit.o :	levelInit.c
	$(CC) $(CFLAGS) -c levelInit.c

clean :
	rm -f $(OBJS) add core
