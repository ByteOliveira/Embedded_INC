cmake_minimum_required(VERSION 3.10)
project(InterNodeCOM_UnitTest)

set(CMAKE_CXX_STANDARD 11)

include(ExternalProject)
ExternalProject_Add(gtest1
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )
ExternalProject_Get_Property(gtest1 source_dir binary_dir)
enable_testing()
################
# Define a test
include_directories(../../.)
add_executable(physical_test physical_interface/Physical.cpp)
######################################
# Configure the test to use GoogleTest
#
# If used often, could be made a macro.
include(GoogleTest)
add_dependencies(physical_test gtest1)
target_link_libraries(physical_test SimpleTest gtest gmock gtest_main)

gtest_discover_tests(physical_test)