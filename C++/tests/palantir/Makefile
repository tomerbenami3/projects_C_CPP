CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wextra -Werror
CPPFLAGS = -I$(INCLUDES_DIR) -I$(PALANTIR_INC_DIR) -I$(PALANTIR_SRC_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
PALANTIR_INC_DIR = $(INCLUDES_DIR)/palantir
PALANTIR_SRC_DIR = $(SOURCES_DIR)/palantir

OBJS = mutest.o rot13.o caeser.o cin.o cout.o messenger.o message.o multi_encoder.o xor.o udp.o tcp.o vigenere.o udp_socket.o file_reader.o tcp_socket.o file_writer.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

rot13.o: $(PALANTIR_SRC_DIR)/rot13.cpp $(PALANTIR_INC_DIR)/rot13.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/rot13.cpp -o rot13.o

caeser.o: $(PALANTIR_SRC_DIR)/caeser.cpp $(PALANTIR_INC_DIR)/caeser.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/caeser.cpp -o caeser.o

nullenc.o: $(PALANTIR_SRC_DIR)/nullenc.cpp $(PALANTIR_INC_DIR)/nullenc.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/nullenc.cpp -o nullenc.o

cin.o: $(PALANTIR_SRC_DIR)/cin.cpp $(PALANTIR_INC_DIR)/cin.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/cin.cpp -o cin.o

cout.o: $(PALANTIR_SRC_DIR)/cout.cpp $(PALANTIR_INC_DIR)/cout.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/cout.cpp -o cout.o

messenger.o: $(PALANTIR_SRC_DIR)/messenger.cpp $(PALANTIR_INC_DIR)/messenger.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/messenger.cpp -o messenger.o

message.o: $(PALANTIR_SRC_DIR)/message.cpp $(PALANTIR_INC_DIR)/message.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/message.cpp -o message.o

multi_encoder.o: $(PALANTIR_SRC_DIR)/multi_encoder.cpp $(PALANTIR_INC_DIR)/multi_encoder.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/multi_encoder.cpp -o multi_encoder.o

xor.o: $(PALANTIR_SRC_DIR)/xor.cpp $(PALANTIR_INC_DIR)/xor.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/xor.cpp -o xor.o

udp.o: $(PALANTIR_SRC_DIR)/udp.cpp $(PALANTIR_INC_DIR)/udp.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/udp.cpp -o udp.o

tcp.o: $(PALANTIR_SRC_DIR)/tcp.cpp $(PALANTIR_INC_DIR)/tcp.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/tcp.cpp -o tcp.o

vigenere.o: $(PALANTIR_SRC_DIR)/vigenere.cpp $(PALANTIR_INC_DIR)/vigenere.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/vigenere.cpp -o vigenere.o

udp_socket.o: $(PALANTIR_SRC_DIR)/udp_socket.cpp $(PALANTIR_INC_DIR)/udp_socket.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/udp_socket.cpp -o udp_socket.o

file_reader.o: $(PALANTIR_SRC_DIR)/file_reader.cpp $(PALANTIR_INC_DIR)/file_reader.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/file_reader.cpp -o file_reader.o

file_writer.o: $(PALANTIR_SRC_DIR)/file_writer.cpp $(PALANTIR_INC_DIR)/file_writer.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/file_writer.cpp -o file_writer.o

tcp_socket.o: $(PALANTIR_SRC_DIR)/tcp_socket.cpp $(PALANTIR_INC_DIR)/tcp_socket.hpp $(PALANTIR_INC_DIR)/abstract_encode.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(PALANTIR_SRC_DIR)/tcp_socket.cpp -o tcp_socket.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
