CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(INTSTACK_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

INTSTACK_DIR = $(INCLUDES_DIR)/ds

OBJS = $(SOURCES_DIR)/ds/intstack.o mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(intstack_DIR)/intstack.o: $(INCLUDES_DIR)/intstack/intstack.hpp
intstack.o: $(INCLUDES_DIR)/ds/intstack.hpp

clean:
	$(RM) $(OBJ) $(TARGET)