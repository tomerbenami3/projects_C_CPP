CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(BF_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
BF_DIR = $(INCLUDES_DIR)/bf
BF_SRC_DIR = $(SOURCES_DIR)/bf

OBJS = mutest.o memory.o cpu.o input.o output.o compiler.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

memory.o: $(BF_SRC_DIR)/memory.cpp $(BF_DIR)/memory.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(BF_SRC_DIR)/memory.cpp -o memory.o

cpu.o: $(BF_SRC_DIR)/cpu.cpp $(BF_DIR)/cpu.hpp 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(BF_SRC_DIR)/cpu.cpp -o cpu.o

input.o: $(BF_SRC_DIR)/input.cpp $(BF_DIR)/input.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(BF_SRC_DIR)/input.cpp -o input.o

output.o: $(BF_SRC_DIR)/output.cpp $(BF_DIR)/output.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(BF_SRC_DIR)/output.cpp -o output.o

compiler.o: $(BF_SRC_DIR)/compiler.cpp $(BF_DIR)/compiler.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(BF_SRC_DIR)/compiler.cpp -o compiler.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
