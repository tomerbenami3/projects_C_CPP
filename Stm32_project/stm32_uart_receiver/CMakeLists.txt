cmake_minimum_required(VERSION 3.16)
project(stm32_uart_receiver)

set(CMAKE_CXX_STANDARD 17)

# Include serial library headers
include_directories(${CMAKE_SOURCE_DIR}/../serial-clean/include)

# Include our own headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link to the compiled serial library
link_directories(${CMAKE_SOURCE_DIR}/../serial-clean/build)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable with all sources
add_executable(receiver main.cpp ${SOURCES})
target_link_libraries(receiver serial)

target_include_directories(receiver
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
