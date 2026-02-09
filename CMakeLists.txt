cmake_minimum_required(VERSION 3.10)
project(RL_control_VLA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# -----------------------------
# Find OpenCV
# -----------------------------
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ----------------------------
# Find Eigen
# ----------------------------
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIRS})

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    src/robot
    src/control
    src/RL
    src/system
)

# -----------------------------
# Source files
# -----------------------------
set(SRC
    src/main.cpp
    src/robot/humanoid.cpp
    src/control/pid.cpp
    src/RL/policy.cpp
    src/RL/vla_policy.cpp
    src/system/latency.cpp
)

# -----------------------------
# Executable
# -----------------------------
add_executable(RL_control_VLA ${SRC})

# -----------------------------
# Link OpenCV
# -----------------------------
target_link_libraries(RL_control_VLA ${OpenCV_LIBS})
