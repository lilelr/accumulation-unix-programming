cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)
set(NetworkIPCSockets_path "/home/lilelr/CLionProjects/cumulation/NetworkIPCSockets")
set(SOCKET_FILES
        ${NetworkIPCSockets_path}/client-socket.cpp ${NetworkIPCSockets_path}/apue.h)

add_executable(client-socket ${SOCKET_FILES})