CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -pedantic -std=c11
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS = 

C_SRC = main.c
CXX_SRC = main.cpp
C_OUT = main_c
CXX_OUT = main_cpp

all: $(C_OUT) $(CXX_OUT)

$(C_OUT): $(C_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(CXX_OUT): $(CXX_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(C_OUT) $(CXX_OUT)