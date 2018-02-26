cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)

include(TestPrograms/CMakeLists.txt)
include(NetworkIPCSockets/CMakeLists.txt)
include(NetworkIPCServer/CMakeLists.txt)
set(SOURCE_FILES
        apue.h main.cpp)

add_executable(main ${SOURCE_FILES})