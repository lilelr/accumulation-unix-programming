cmake_minimum_required(VERSION 3.7)
project(acumulation)

set(CMAKE_CXX_STANDARD 11)

set(SLEEP_SOURCE_FILES
        SleepSeveralSeconds.cpp)

add_executable(sleep_several_seconds ${SLEEP_SOURCE_FILES})