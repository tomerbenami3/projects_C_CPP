CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(OBJECTPOOL_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJECTPOOL_DIR = $(INCLUDES_DIR)/dp

OBJS = mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

object_pool.o: $(OBJECTPOOL_DIR)/object_pool.hpp

clean:
	$(RM) $(OBJ) $(TARGET)