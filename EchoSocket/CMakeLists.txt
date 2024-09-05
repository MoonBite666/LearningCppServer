cmake_minimum_required(VERSION 3.28)
project(EchoSocket)

set(CMAKE_CXX_STANDARD 20)

add_executable(echo_server
        Server.cpp
        Server.h
)
add_executable(echo_client
        Client.cpp
        Client.h
)