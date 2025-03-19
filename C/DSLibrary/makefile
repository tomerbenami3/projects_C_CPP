TARGET = libds.so
CC = gcc
CFLAGS = -g -shared
OBJS = vector.o stack.o queue.o dlist.o HashMap.o heap.o
VECTOR_PATH = ../Vectornew/
STACK_PATH = ../Vector/
QUEUE_PATH = ../Queue/
DLIST_PATH = ../DoubleLinkedList/
HASH_PATH = ../HashMapnew/
HEAP_PATH = ../heap/


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


vector.o: $(VECTOR_PATH)vector.c $(VECTOR_PATH)vector.h
	$(CC) -g -c -fPIC -I $(VECTOR_PATH) $(VECTOR_PATH)vector.c

stack.o: $(STACK_PATH)stack.c $(STACK_PATH)stack.h $(VECTOR_PATH)vector.h
	$(CC) -g -c -fPIC -I $(VECTOR_PATH) $(STACK_PATH)stack.c

queue.o: $(QUEUE_PATH)queue.c $(QUEUE_PATH)queue.h
	$(CC) -g -c -fPIC -I $(QUEUE_PATH) $(QUEUE_PATH)queue.c

dlist.o: $(DLIST_PATH)dlist.c $(DLIST_PATH)dlist.h
	$(CC) -g -c -fPIC -I $(DLIST_PATH) $(DLIST_PATH)dlist.c

HashMap.o: $(HASH_PATH)HashMap.c $(HASH_PATH)HashMap.h $(DLIST_PATH)dlist.h
	$(CC) -g -c -fPIC -I $(HASH_PATH) -I $(DLIST_PATH) $(HASH_PATH)HashMap.c

heap.o: $(HEAP_PATH)heap.c $(HEAP_PATH)heap.h $(VECTOR_PATH)vector.h
	$(CC) -g -c -fPIC -I $(HEAP_PATH) -I $(VECTOR_PATH) $(HEAP_PATH)heap.c

clean:
	rm -f $(TARGET) $(OBJS)
