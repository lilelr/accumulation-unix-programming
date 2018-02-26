cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)

set(SLEEP_SOURCE_FILES
        /home/lilelr/CLionProjects/cumulation/Chapter3FIleIO/Read.cpp)

add_executable(file_read ${SLEEP_SOURCE_FILES})