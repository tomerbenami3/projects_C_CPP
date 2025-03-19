CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(HASHTABLETHREADSAFE_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

HASHTABLETHREADSAFE_DIR = $(INCLUDES_DIR)/mt

OBJS = mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

leaks: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

races: $(TARGET)
	valgrind --tool=helgrind ./$(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

object_pool.o: $(HASHTABLETHREADSAFE_DIR)/hash_table.hpp

clean:
	$(RM) $(OBJ) $(TARGET)