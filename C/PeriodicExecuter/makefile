TARGET = app.out
CC = gcc
CFLAGS = -g
OBJS = app.o executor.o task.o calctime.o
LDS_PATH = ../DSLibrary/
VECTOR_PATH = ../Vectornew/
HEAP_PATH = ../Heap/

$(TARGET): $(OBJS)
	$(CC) -g -o $(TARGET) $(OBJS) -L$(LDS_PATH) -lds

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

executor.o: executor.c executor.h $(VECTOR_PATH)vector.h $(HEAP_PATH)heap.h
	$(CC) $(CFLAGS) -I $(VECTOR_PATH) -I $(HEAP_PATH) -c executor.c

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

calctime.o: calctime.c calctime.h
	$(CC) $(CFLAGS) -c calctime.c

clean:
	rm -f $(TARGET) $(OBJS)

# LD_LIBRARY_PATH:$LD_LIBRARY_PATH:../DSLibrary/
