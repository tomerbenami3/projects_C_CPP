TARGET = hearts
CC = gcc
CFLAGS = -g
OBJS = main.o game.o player.o deck.o round.o vector.o ui.o roundtest.o
VECTOR_PATH = ../Vectornew/

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h player.h round.h
	$(CC) $(CFLAGS) -c game.c

player.o: player.c player.h $(VECTOR_PATH)vector.h
	$(CC) $(CFLAGS) -c -I $(VECTOR_PATH) player.c

deck.o: deck.c deck.h cards.h $(VECTOR_PATH)vector.h
	$(CC) $(CFLAGS) -c -I $(VECTOR_PATH) deck.c

round.o: round.c round.h
	$(CC) $(CFLAGS) -c round.c

vector.o: $(VECTOR_PATH)vector.c $(VECTOR_PATH)vector.h
	$(CC) $(CFLAGS) -c -I $(VECTOR_PATH) $(VECTOR_PATH)vector.c

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c -I $(VECTOR_PATH) ui.c

clean:
	rm -f $(TARGET) $(OBJS)
