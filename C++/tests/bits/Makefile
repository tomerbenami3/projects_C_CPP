CXX = g++
CC = $(CXX)

CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
# CPPFLAGS = -I$(INCLUDES_DIR) -I$(ALGO_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

# ALGO_DIR = $(INCLUDES_DIR)/algo

OBJS = app.o

TARGET = app

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

app.o: app.cpp

clean:
	$(RM) $(OBJ) $(TARGET)