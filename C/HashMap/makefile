TARGET = output.out
CC = gcc
CFLAGS =  -g   # Add the include path for vector.h
OBJS = main.o dlist.o hashmap.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c hashmap.h ../DoubleLinkedList/dlist.h
	$(CC) $(CFLAGS) -c main.c

dlist.o: ../DoubleLinkedList/dlist.c ../DoubleLinkedList/dlist.h  # Corrected path to vector.h
	$(CC) $(CFLAGS) -c ../DoubleLinkedList/dList.c

hashmap.o: hashmap.c hashmap.h ../DoubleLinkedList/dlist.h  # Corrected path to vector.h
	$(CC) $(CFLAGS) -c hashmap.c

clean:
	rm -f $(TARGET) $(OBJS)