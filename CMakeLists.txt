cmake_minimum_required(VERSION 3.20)
project(Wasalni_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wasalni_final
        Colors.cpp
        edge.cpp
        edge.h
        FileHandling.cpp
        FileHandling.h
        Graph.cpp
        Graph.h
        main.cpp
        shortestPath.cpp
        shortestPath.h
        StartMenu.cpp
        StartMenu.h
        Validation.cpp
        Validation.h)
