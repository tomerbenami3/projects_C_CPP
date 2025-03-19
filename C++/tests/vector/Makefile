CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(ALGO_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

ALGO_DIR = $(INCLUDES_DIR)/algo

OBJS = mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

vector.o: $(ALGO_DIR)/vector.hpp

clean:
	$(RM) $(OBJ) $(TARGET)