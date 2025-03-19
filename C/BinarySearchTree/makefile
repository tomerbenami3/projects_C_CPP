TARGET = output.out
CC = gcc
CFLAGS = -g
OBJS = main.o  bstree.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c bstree.h
	$(CC) $(CFLAGS) -c main.c


bstree.o: bstree.c bstree.h 
	$(CC) $(CFLAGS) -c bstree.c

clean:
	rm -f $(TARGET) $(OBJS)