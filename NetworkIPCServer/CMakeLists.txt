cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)
set(NetworkIPCSockets_path "/home/lilelr/CLionProjects/cumulation/NetworkIPCServer")
set(SOCKET_FILES
        ${NetworkIPCSockets_path}/server-socket.cpp)

add_executable(server-socket ${SOCKET_FILES})