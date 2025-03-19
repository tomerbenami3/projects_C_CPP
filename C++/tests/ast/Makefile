CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(AST_INC_DIR) -I$(AST_SRC_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
AST_INC_DIR = $(INCLUDES_DIR)/ast
AST_SRC_DIR = $(SOURCES_DIR)/ast

OBJS = mutest.o op_node.o var_node.o value_node.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

op_node.o: $(AST_SRC_DIR)/op_node.cpp $(AST_INC_DIR)/op_node.hpp $(AST_INC_DIR)/abstract_node.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(AST_SRC_DIR)/op_node.cpp -o op_node.o

var_node.o: $(AST_SRC_DIR)/var_node.cpp $(AST_INC_DIR)/var_node.hpp $(AST_INC_DIR)/abstract_node.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(AST_SRC_DIR)/var_node.cpp -o var_node.o

value_node.o: $(AST_SRC_DIR)/value_node.cpp $(AST_INC_DIR)/value_node.hpp $(AST_INC_DIR)/abstract_node.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(AST_SRC_DIR)/value_node.cpp -o value_node.o


mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
