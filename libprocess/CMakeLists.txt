cmake_minimum_required(VERSION 3.8)
project(libprocess_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#include_directories("/usr/local/include/process")
#find_package (glog)
set(SOURCE_FILES  simplesever.cpp)
add_executable(libprocess_test ${SOURCE_FILES})
#
#find_package(Threads REQUIRED)
#if(THREADS_HAVE_PTHREAD_ARG)
#    set_property(TARGET libprocess_test PROPERTY COMPILE_OPTIONS "-pthread")
#    set_property(TARGET libprocess_test PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#    target_link_libraries(libprocess_test "${CMAKE_THREAD_LIBS_INIT}")
#endif()
#
##find_package(ZLIB)
##if (ZLIB_FOUND)
##     include_directories(${ZLIB_INCLUDE_DIRS})
##     target_link_libraries(libprocess_test ${ZLIB_LIBRARIES})
## endif()
##message( ${ZLIB_LIBRARIES})
#
#target_link_libraries(libprocess_test glog z /home/lilelr/open-source/mesos/build/3rdparty/libprocess/.libs/libprocess.a)

target_link_libraries(libprocess_test /usr/local/lib/libmesos.so)

set(PROMISE_ANG_FUTURE_SOURCE_FILES  PromiseAndFuture.cpp)
add_executable(promise-future ${PROMISE_ANG_FUTURE_SOURCE_FILES})
target_link_libraries(promise-future /usr/local/lib/libmesos.so)
