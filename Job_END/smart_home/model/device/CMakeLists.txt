cmake_minimum_required(VERSION 3.16)
project(device)

set(CMAKE_CXX_STANDARD 23)

add_library(device STATIC source/device.cpp)

target_include_directories(device PUBLIC include)