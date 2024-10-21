# Minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(FlightProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the src directory where headers are located
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add HW1_8_CPP executable with relevant source files
add_executable(HW1_8_CPP 
    src/HW1_8_CPP.cpp 
    src/Plane.cpp 
    src/Pilot.cpp 
    src/FlightInfo.cpp
)

# Add HW1_Q_1 executable (no Plane, Pilot, or FlightInfo needed)
add_executable(HW1_Q_1 
    src/HW1_Q_1.cpp
)

# Add HW1_Q_2_6 executable with Plane and Pilot dependencies
add_executable(HW1_Q_2_6 
    src/HW1_Q_2-6.cpp 
    src/Plane.cpp 
    src/Pilot.cpp 
    src/FlightInfo.cpp
)

# Add HW1_Q_7_C executable with Plane and Pilot dependencies
add_executable(HW1_Q_7_C 
    src/HW1_Q_7_C.cpp 
    src/Plane.cpp 
    src/Pilot.cpp 
    src/FlightInfo.cpp
)
