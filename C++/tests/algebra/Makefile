CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(RATIONAL_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

RATIONAL_DIR = $(INCLUDES_DIR)/algebra

OBJS = $(SOURCES_DIR)/algebra/rational.o mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(RATIONAL_DIR)/rational.o: $(INCLUDES_DIR)/rational/rational.hpp
rational.o: $(INCLUDES_DIR)/algebra/rational.hpp

clean:
	$(RM) $(OBJ) $(TARGET)