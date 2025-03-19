CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(LC3_INC_DIR) -I$(LC3_SRC_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
LC3_INC_DIR = $(INCLUDES_DIR)/lc3
LC3_SRC_DIR = $(SOURCES_DIR)/lc3

OBJS = mutest.o registerfile.o flags.o alu.o memory.o file_manager.o isa.o cpu.o trap.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

registerfile.o: $(LC3_SRC_DIR)/registerfile.cpp $(LC3_INC_DIR)/registerfile.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/registerfile.cpp -o registerfile.o

flags.o: $(LC3_SRC_DIR)/flags.cpp $(LC3_INC_DIR)/flags.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/flags.cpp -o flags.o

alu.o: $(LC3_SRC_DIR)/alu.cpp $(LC3_INC_DIR)/alu.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/alu.cpp -o alu.o

memory.o: $(LC3_SRC_DIR)/memory.cpp $(LC3_INC_DIR)/memory.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/memory.cpp -o memory.o

file_manager.o: $(LC3_SRC_DIR)/file_manager.cpp $(LC3_INC_DIR)/file_manager.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/file_manager.cpp -o file_manager.o

isa.o: $(LC3_SRC_DIR)/isa.cpp $(LC3_INC_DIR)/isa.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/isa.cpp -o isa.o

cpu.o: $(LC3_SRC_DIR)/cpu.cpp $(LC3_INC_DIR)/cpu.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/cpu.cpp -o cpu.o

trap.o: $(LC3_SRC_DIR)/trap.cpp $(LC3_INC_DIR)/trap.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(LC3_SRC_DIR)/trap.cpp -o trap.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
