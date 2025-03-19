TARGET = output.out
CC = gcc
CFLAGS = -g
OBJS = main.o  dlist.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c dlist.h
	$(CC) $(CFLAGS) -c main.c


dlist.o: dlist.c dlist.h 
	$(CC) $(CFLAGS) -c dlist.c

clean:
	rm -f $(TARGET) $(OBJS)