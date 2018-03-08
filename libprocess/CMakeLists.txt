

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

# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()


set(main_SOURCE_FILES main.cpp)
add_executable(libprocess-main ${main_SOURCE_FILES})
target_link_libraries(libprocess-main /usr/local/lib/libmesos.so)

set(MESSAGE_EVENT_SOURCE_FILES  messageevent.cpp)
add_executable(message-event ${MESSAGE_EVENT_SOURCE_FILES})
target_link_libraries(message-event /usr/local/lib/libmesos.so)


# Find required protobuf package
set(PROTOBUF_VERSION "3.5.1")

find_package(Protobuf ${PROTOBUF_VERSION} EXACT REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()


include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS addressbook.proto)

set(protobuf_MESSAGE_EVENT_SOURCE_FILES  protobufmessageevent.cpp)
add_executable(protobuf-message-event ${protobuf_MESSAGE_EVENT_SOURCE_FILES} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(protobuf-message-event /usr/local/lib/libmesos.so)

set(client_protobuf_MESSAGE_EVENT_SRCS  client_protobuf_message_event.cpp)
add_executable(client_protobuf ${client_protobuf_MESSAGE_EVENT_SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(client_protobuf /usr/local/lib/libmesos.so)


set(PROMISE_ANG_FUTURE_SOURCE_FILES  PromiseAndFuture.cpp)
add_executable(promise-future ${PROMISE_ANG_FUTURE_SOURCE_FILES})
target_link_libraries(promise-future /usr/local/lib/libmesos.so)


set(FOO_SOURCE_FILES  FooProcess.cpp)
add_executable(foo-process ${FOO_SOURCE_FILES})
target_link_libraries(foo-process /usr/local/lib/libmesos.so)


set(DELAY_SOURCE_FILES  delay.cpp)
add_executable(delay-process ${DELAY_SOURCE_FILES})
target_link_libraries(delay-process /usr/local/lib/libmesos.so)



set(master-slave-SOURCE_FILES  MyMaster.cpp)
add_executable(master-slave ${master-slave-SOURCE_FILES})
target_link_libraries(master-slave /usr/local/lib/libmesos.so)
