CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(RATIONAL_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

RATIONAL_DIR = $(INCLUDES_DIR)/algebra

OBJS = mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(RATIONAL_DIR)/vectors2d.o: $(INCLUDES_DIR)/vectors2d/vectors2d.hpp
vectors2d.o: $(INCLUDES_DIR)/algebra/vectors2d.hpp

clean:
	$(RM) $(OBJ) $(TARGET)