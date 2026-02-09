cmake_minimum_required(VERSION 3.10)

project(RL_control_project)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization + warnings (systems-friendly)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

# Where headers live
include_directories(src)

# All source files
add_executable(RL_control_project
    src/main.cpp
    src/robot/humanoid.cpp
    src/control/pid.cpp
    src/RL/policy.cpp
    src/system/latency.cpp
)