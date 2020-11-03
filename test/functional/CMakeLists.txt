cmake_minimum_required(VERSION 3.10)
project(InterNodeCOM_FuncTest)
set(CMAKE_CXX_STANDARD 11)

include_directories(../../.)

add_executable(physical_test physical_interface/demo_physical.cpp)
target_link_libraries(physical_test INC_PH)