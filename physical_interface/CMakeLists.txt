
cmake_minimum_required(VERSION 3.10)
project(InterNodeCOM_PH)

set(CMAKE_CXX_STANDARD 11)

include_directories(.. , ../utils , third_party/serial/include)

add_subdirectory(third_party/serial)

add_library(INC_PH_LOOPBACK loopback/loopback.cpp)

add_library(INC_PH_SERIAL serial_interface/serial.cpp)


add_library(INC_PH STATIC Physical.cpp Physical.h )
target_link_libraries(INC_PH_SERIAL PUBLIC serial)
target_link_libraries(INC_PH INC_PH_SERIAL INC_PH_LOOPBACK)