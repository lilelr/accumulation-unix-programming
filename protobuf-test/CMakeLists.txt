
set(CMAKE_CXX_STANDARD 11)

set(protobuf-test_FILES main.cpp )


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
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS addressbook.proto Test1.proto)



add_executable(protobuf-test ${protobuf-test_FILES} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(protobuf-test ${PROTOBUF_LIBRARIES})



set(protobuf-test1_FILES Test1.cpp )
add_executable(protobuf-Test1 ${protobuf-test1_FILES} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(protobuf-Test1 ${PROTOBUF_LIBRARIES})
