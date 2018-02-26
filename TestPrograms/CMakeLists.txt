cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)

set(SLEEP_SOURCE_FILES
        /home/lilelr/CLionProjects/cumulation/TestPrograms/SleepSeveralSeconds.cpp)

add_executable(sleep_several_seconds ${SLEEP_SOURCE_FILES})