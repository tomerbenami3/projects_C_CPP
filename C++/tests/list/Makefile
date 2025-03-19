CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(LIST_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

LIST_DIR = $(INCLUDES_DIR)/ds

OBJS = mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

list.o: $(LIST_DIR)/list.hpp

clean:
	$(RM) $(OBJ) $(TARGET)