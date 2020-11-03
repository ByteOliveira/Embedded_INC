cmake_minimum_required(VERSION 3.10)
project(InterNodeCOM)

set(CMAKE_CXX_STANDARD 11)

include_directories(. , physical_interface/serial/include)
add_subdirectory(physical_interface)
add_subdirectory(data_link)

add_executable(InterNodeCOM
        library.cpp
        library.h)


###########################################################
##################TEST##############################
###########################################################

#add_subdirectory(test/unit)
add_subdirectory(test/functional)

###########################################################
##################TEST##############################
###########################################################