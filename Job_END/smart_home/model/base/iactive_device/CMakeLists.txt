cmake_minimum_required(VERSION 3.16)
project(iactive_device)

set(CMAKE_CXX_STANDARD 23)

add_library(iactive_device INTERFACE)

target_include_directories(iactive_device INTERFACE include)