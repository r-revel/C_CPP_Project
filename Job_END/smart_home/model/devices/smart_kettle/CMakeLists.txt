cmake_minimum_required(VERSION 3.16)
project(smart_kettle)

set(CMAKE_CXX_STANDARD 23)

add_library(smart_kettle STATIC source/smart_kettle.cpp)

target_include_directories(smart_kettle PUBLIC include)

target_link_libraries(smart_kettle PUBLIC idevice device isensor_device iactive_device)