CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(EXECUTOR_INC_DIR) -I$(EXECUTOR_SRC_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
EXECUTOR_INC_DIR = $(INCLUDES_DIR)/executor
EXECUTOR_SRC_DIR = $(SOURCES_DIR)/executor

OBJS = mutest.o periodic_executor.o time_spec.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

periodic_executor.o: $(EXECUTOR_SRC_DIR)/periodic_executor.cpp $(EXECUTOR_INC_DIR)/periodic_executor.hpp $(EXECUTOR_INC_DIR)/abstract_executor.hpp $(EXECUTOR_INC_DIR)/time_calculations.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(EXECUTOR_SRC_DIR)/periodic_executor.cpp -o periodic_executor.o

time_spec.o: $(EXECUTOR_SRC_DIR)/time_spec.cpp $(EXECUTOR_INC_DIR)/time_spec.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(EXECUTOR_SRC_DIR)/time_spec.cpp -o time_spec.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
