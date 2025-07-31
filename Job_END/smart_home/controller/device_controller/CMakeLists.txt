cmake_minimum_required(VERSION 3.16)
project(device_controller)

set(CMAKE_CXX_STANDARD 23)

add_library(device_controller STATIC source/device_controller.cpp)

target_include_directories(device_controller PUBLIC include)

target_link_libraries(device_controller PUBLIC idevice isensor_device iactive_device)