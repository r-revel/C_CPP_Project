cmake_minimum_required(VERSION 3.16)
project(idevice)

set(CMAKE_CXX_STANDARD 23)

add_library(idevice INTERFACE)

target_include_directories(idevice INTERFACE include)