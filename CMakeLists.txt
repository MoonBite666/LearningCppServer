cmake_minimum_required(VERSION 3.28)
project(LearningCppServer)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_SYSTEM_NAME MATCHES "CYGWIN")
    message(STATUS "CYGWIN")
endif ()

add_subdirectory(SimpleSocket)
add_subdirectory(EchoSocket)
add_subdirectory(EpollServer)