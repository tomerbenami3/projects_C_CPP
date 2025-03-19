include ../Makefile.common

MODULE_DIR = $(INCLUDES_DIR)/rpn

# Define source and object file for token.cpp
TOKEN_SRC = $(SOURCES_DIR)/rpn/token.cpp
TOKEN_OBJ = token.o

# Ensure mutest.o depends on token.hpp
mutest.o: $(MODULE_DIR)/token.hpp

# Build token.o from token.cpp
$(TOKEN_OBJ): $(TOKEN_SRC) $(MODULE_DIR)/token.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Include token.o in the target build
OBJS = mutest.o $(TOKEN_OBJ)
TARGET = mutest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
