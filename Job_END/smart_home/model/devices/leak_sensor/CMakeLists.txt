cmake_minimum_required(VERSION 3.16)
project(leak_sensor)

set(CMAKE_CXX_STANDARD 23)

add_library(leak_sensor STATIC source/leak_sensor.cpp)

target_include_directories(leak_sensor PUBLIC include)

target_link_libraries(leak_sensor PUBLIC idevice device isensor_device)