cmake_minimum_required(VERSION 3.7)
project(acumulation)

#set(CMAKE_CXX_STANDARD 11)

add_subdirectory(TestPrograms)
add_subdirectory(NetworkIPCSockets)
#include(libprocess/CMakeLists.txt)
#add_subdirectory(libprocess)
#include(NetworkIPCServer/CMakeLists.txt)
add_subdirectory(Chapter3FIleIO)
add_subdirectory(chapter8ProcessControl)
add_subdirectory(linux_library_function_learning)
add_subdirectory(chapter15inerprocess_communication)


#add_subdirectory(protobuf-test)

set(SOURCE_FILES
        apue.h main.cpp linux_library_function_learning/getloadavg.cpp chapter15inerprocess_communication/popen_start.cpp)

add_executable(main ${SOURCE_FILES})