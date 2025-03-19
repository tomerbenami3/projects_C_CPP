TARGET = main.out
CC = gcc
CFLAGS =  -g   # Add the include path for vector.h
OBJS = main.o dlist.o HashMap.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c HashMap.h ../DoubleLinkedList/dlist.h
	$(CC) $(CFLAGS) -c main.c

DList.o: ../DoubleLinkedList/dlist.c ../DoubleLinkedList/dlist.h  # Corrected path to vector.h
	$(CC) $(CFLAGS) -c ../DoubleLinkedList/dlist.c

HashMap.o: HashMap.c HashMap.h ../DoubleLinkedList/dlist.h  # Corrected path to vector.h
	$(CC) $(CFLAGS) -c HashMap.c

clean:
	rm -f $(TARGET) $(OBJS)