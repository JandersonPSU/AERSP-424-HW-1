cmake_minimum_required(VERSION 3.10)
project(FlightProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the src directory for header files
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add executables, specifying the source files
add_executable(HW1_8_CPP src/HW1_8_CPP.cpp)
add_executable(HW1_Q_1 src/HW1_Q_1.cpp)
add_executable(HW1_Q_2_6 src/HW1_Q_2-6.cpp)
add_executable(HW1_Q_7_C src/HW1_Q_7_C.cpp)
