TARGET = output.out
CC = gcc
CFLAGS = -g -pedantic
OBJS = main.o  queue.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c queue.h
	$(CC) $(CFLAGS) -c main.c


queue.o: queue.c queue.h 
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f $(TARGET) $(OBJS)