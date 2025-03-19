CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(SEMAPHORE_INC_DIR) -I$(SEMAPHORE_SRC_DIR)

INCLUDES_DIR = ../../../inc
SOURCES_DIR = ../../../src
SEMAPHORE_INC_DIR = $(INCLUDES_DIR)/mt
SEMAPHORE_SRC_DIR = $(SOURCES_DIR)/mt

OBJS = mutest.o semaphore.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

semaphore.o: $(SEMAPHORE_SRC_DIR)/semaphore.cpp $(SEMAPHORE_INC_DIR)/semaphore.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SEMAPHORE_SRC_DIR)/semaphore.cpp -o semaphore.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
