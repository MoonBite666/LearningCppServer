cmake_minimum_required(VERSION 3.28)
project(SimpleSocket)

set(CMAKE_CXX_STANDARD 20)

add_executable(server
        Server.cpp
        Server.h
)
add_executable(client
        Client.cpp
        Client.h
)