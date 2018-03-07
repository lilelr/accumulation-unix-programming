cmake_minimum_required(VERSION 3.8)
project(acumulation)

#set(CMAKE_CXX_STANDARD 11)

add_subdirectory(TestPrograms)
add_subdirectory(NetworkIPCSockets)
#include(libprocess/CMakeLists.txt)
add_subdirectory(libprocess)
#include(NetworkIPCServer/CMakeLists.txt)
add_subdirectory(Chapter3FIleIO)

set(SOURCE_FILES
        apue.h main.cpp)

add_executable(main ${SOURCE_FILES})