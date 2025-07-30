cmake_minimum_required(VERSION 3.16)
project(air_conditioner)

set(CMAKE_CXX_STANDARD 23)

add_library(air_conditioner STATIC source/air_conditioner.cpp)

target_include_directories(air_conditioner PUBLIC include)

target_link_libraries(air_conditioner PUBLIC idevice device isensor_device iactive_device)