cmake_minimum_required(VERSION 3.15)
project(MicroProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MicroProject
        Directive.h
        GateFactory.h
        Gates.h
        main.cpp
        Node.h
        Node_old.h)
