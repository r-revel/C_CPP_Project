cmake_minimum_required(VERSION 3.16)
project(devices)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(smart_bulb)
add_subdirectory(thermometer)
add_subdirectory(smart_kettle)
add_subdirectory(leak_sensor)
add_subdirectory(air_conditioner)