cmake_minimum_required(VERSION 3.16)
project(active_device)

set(CMAKE_CXX_STANDARD 23)

add_library(active_device STATIC source/active_device.cpp)

target_include_directories(active_device PUBLIC include)
target_link_libraries(active_device PUBLIC device)