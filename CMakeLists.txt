cmake_minimum_required(VERSION 3.15)

project(graph_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "headers/*.hpp")

include_directories("headers")
add_executable(graph_engine
               ${SOURCES}
               ${HEADERS})
