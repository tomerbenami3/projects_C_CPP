# makefile vector

TARGET = output.out
CC = gcc
CFLAGS = -g
OBJS = vector.o main.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
	
main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET) $(OBJS)

