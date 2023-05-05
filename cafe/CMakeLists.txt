cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cafe)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(cafe ${SOURCES})