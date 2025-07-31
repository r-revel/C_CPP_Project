cmake_minimum_required(VERSION 3.16)
project(isensor_device)

set(CMAKE_CXX_STANDARD 23)

add_library(isensor_device INTERFACE)

target_include_directories(isensor_device INTERFACE include)