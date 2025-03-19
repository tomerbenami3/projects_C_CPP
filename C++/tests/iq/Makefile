CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(IQ_INC_DIR) -I$(IQ_SRC_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
IQ_INC_DIR = $(INCLUDES_DIR)/iq
IQ_SRC_DIR = $(SOURCES_DIR)/iq

OBJS = mutest.o 

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

containers.o: $(IQ_INC_DIR)/containers.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o containers.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
