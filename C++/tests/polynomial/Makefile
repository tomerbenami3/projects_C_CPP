CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(ALGEBRA_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

ALGEBRA_DIR = $(INCLUDES_DIR)/algebra

OBJS = $(SOURCES_DIR)/algebra/polynomial.o $(SOURCES_DIR)/algebra/rational.o mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(ALGEBRA_DIR)/polynomial.o: $(INCLUDES_DIR)/polynomial/polynomial.hpp
polynomial.o: $(INCLUDES_DIR)/algebra/polynomial.hpp
rational.o: $(INCLUDES_DIR)/algebra/rational.hpp

clean:
	$(RM) $(OBJ) $(TARGET)