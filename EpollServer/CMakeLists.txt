cmake_minimum_required(VERSION 3.28)
project(Epoll)

set(CMAKE_CXX_STANDARD 20)

#if(WIN32)
#
#endif ()

add_executable(epoll_client
    Client.cpp
)

add_executable(epoll_server
    Server.cpp
)

if(CMAKE_SYSTEM_NAME MATCHES "CYGWIN")
    message(STATUS "Configuring for Windows")
    include_directories(../wepoll)
    add_library(wepoll
        ../wepoll/sys/epoll.c
#        ../wepoll/sys/epoll.h
    )
    target_link_libraries(epoll_server
        wepoll
    )
endif ()