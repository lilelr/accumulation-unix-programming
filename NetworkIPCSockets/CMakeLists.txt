
set(CMAKE_CXX_STANDARD 11)
set(NetworkIPCSockets_path "/home/lilelr/CLionProjects/cumulation/NetworkIPCSockets")
set(SOCKET_FILES
        client-socket.cpp apue.h)

add_executable(client-socket ${SOCKET_FILES})