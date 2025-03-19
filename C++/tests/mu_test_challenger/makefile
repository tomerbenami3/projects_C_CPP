CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(CHALLENGE_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

CHALLENGE_DIR = $(INCLUDES_DIR)/challenge

OBJS = $(SOURCES_DIR)/challenge/challenger_1.o challenge_accepted.o

TARGET = challenge_accepted

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)

$(CHALLENGE_DIR)/challenger_1.o: $(INCLUDES_DIR)/challenge/challenger_1.hpp
challenge_accepted.o: $(INCLUDES_DIR)/challenge/challenger_1.hpp

clean:
	$(RM) $(OBJ) $(TARGET)