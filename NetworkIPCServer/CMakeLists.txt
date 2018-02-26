cmake_minimum_required(VERSION 3.8)
project(cumulation)

set(CMAKE_CXX_STANDARD 11)
set(NetworkIPCSockets_path "/home/lilelr/open-source/accumulation-unix-programming/NetworkIPCServer")
set(SOCKET_FILES
        ${NetworkIPCSockets_path}/server-socket.cpp)
set(SOCKET_FORK_FILES
        ${NetworkIPCSockets_path}/server-socket-fork.cpp)
add_executable(server-socket ${SOCKET_FILES})
add_executable(server-socket-fork ${SOCKET_FORK_FILES})