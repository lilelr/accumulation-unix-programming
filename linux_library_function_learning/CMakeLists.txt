cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)

set(getloadavg_SRCS getloadavg.cpp)

add_executable(getloadavg_main ${getloadavg_SRCS})
