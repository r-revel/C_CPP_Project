cmake_minimum_required(VERSION 3.16)
project(thermometer)

set(CMAKE_CXX_STANDARD 23)

add_library(thermometer STATIC source/thermometer.cpp)

target_include_directories(thermometer PUBLIC include)

target_link_libraries(thermometer PUBLIC idevice device isensor_device)