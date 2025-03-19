CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(DS_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

DS_DIR = $(INCLUDES_DIR)/ds

OBJS = $(SOURCES_DIR)/ds/intqueue.o $(SOURCES_DIR)/ds/intstack.o mutest.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(DS_DIR)/intqueue.o: $(INCLUDES_DIR)/intqueue/intqueue.hpp
intqueue.o: $(INCLUDES_DIR)/ds/intqueue.hpp
intstack.o: $(INCLUDES_DIR)/ds/intstack.hpp

clean:
	$(RM) $(OBJ) $(TARGET)

## find . -name "*.o" -type f -delete
## git rm --cached -r "*.o"