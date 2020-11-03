cmake_minimum_required(VERSION 3.10)
project(InterNodeCOM_PH)

set(CMAKE_CXX_STANDARD 11)

include_directories(.. , ../utils third_party/yahdlc/C )

add_library(framing framitization/Frame.cpp framitization/Framer.cpp)