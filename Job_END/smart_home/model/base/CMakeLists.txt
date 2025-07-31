cmake_minimum_required(VERSION 3.16)
project(base)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(isensor_device)
add_subdirectory(iactive_device)
add_subdirectory(idevice)