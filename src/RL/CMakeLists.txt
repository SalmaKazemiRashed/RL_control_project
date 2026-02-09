cmake_minimum_required(VERSION 3.10)
project(VLA_RL)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(SOURCES
    vla.cpp
    train_vla.cpp
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add executable
add_executable(train_vla ${SOURCES})

