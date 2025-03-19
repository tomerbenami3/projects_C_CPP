CXX = g++
CXXFLAGS = -std=c++17
CPPFLAGS = -I$(INCLUDES_DIR) -I$(ARKA_INC_DIR) -I$(ARKA_SRC_DIR) -I/opt/homebrew/Cellar/sfml/3.0.0/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/3.0.0/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

INCLUDES_DIR = ../../../inc
SOURCES_DIR = ../../../src
ARKA_INC_DIR = $(INCLUDES_DIR)/arkanoid
ARKA_SRC_DIR = $(SOURCES_DIR)/arkanoid

OBJS = mutest.o game.o ball.o paddle.o input.o brick.o level.o main_menu.o high_score_manager.o high_score_screen.o sound_manager.o topten_screen.o

TARGET = mutest

all: $(TARGET)

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

game.o: $(ARKA_SRC_DIR)/game.cpp $(ARKA_INC_DIR)/game.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/game.cpp -o game.o

ball.o: $(ARKA_SRC_DIR)/ball.cpp $(ARKA_INC_DIR)/ball.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/ball.cpp -o ball.o

paddle.o: $(ARKA_SRC_DIR)/paddle.cpp $(ARKA_INC_DIR)/paddle.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/paddle.cpp -o paddle.o

input.o: $(ARKA_SRC_DIR)/input.cpp $(ARKA_INC_DIR)/input.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/input.cpp -o input.o

brick.o: $(ARKA_SRC_DIR)/brick.cpp $(ARKA_INC_DIR)/brick.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/brick.cpp -o brick.o

level.o: $(ARKA_SRC_DIR)/level.cpp $(ARKA_INC_DIR)/level.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/level.cpp -o level.o

main_menu.o: $(ARKA_SRC_DIR)/main_menu.cpp $(ARKA_INC_DIR)/main_menu.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/main_menu.cpp -o main_menu.o

high_score_manager.o: $(ARKA_SRC_DIR)/high_score_manager.cpp $(ARKA_INC_DIR)/high_score_manager.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/high_score_manager.cpp -o high_score_manager.o

high_score_screen.o: $(ARKA_SRC_DIR)/high_score_screen.cpp $(ARKA_INC_DIR)/high_score_screen.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/high_score_screen.cpp -o high_score_screen.o

sound_manager.o: $(ARKA_SRC_DIR)/sound_manager.cpp $(ARKA_INC_DIR)/sound_manager.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/sound_manager.cpp -o sound_manager.o

topten_screen.o: $(ARKA_SRC_DIR)/topten_screen.cpp $(ARKA_INC_DIR)/topten_screen.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(ARKA_SRC_DIR)/topten_screen.cpp -o topten_screen.o

mutest.o: mutest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c mutest.cpp -o mutest.o

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all check clean
