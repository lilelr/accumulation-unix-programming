cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)

set(getloadavg_SRCS getloadavg.cpp)
add_executable(getloadavg_main ${getloadavg_SRCS})

set(getenv_SRCS getenv.cpp)
add_executable(getenv_main ${getenv_SRCS})


set(cpu_usage_by_top_SRCS cpu_usage_by_top.cpp)
add_executable(cpu_usage_by_top_main ${cpu_usage_by_top_SRCS})
