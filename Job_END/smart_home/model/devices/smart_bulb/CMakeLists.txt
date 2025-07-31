cmake_minimum_required(VERSION 3.16)
project(smart_bulb)

set(CMAKE_CXX_STANDARD 23)

add_library(smart_bulb STATIC source/smart_bulb.cpp)

target_include_directories(smart_bulb PUBLIC include)

target_link_libraries(smart_bulb PUBLIC idevice device iactive_device)