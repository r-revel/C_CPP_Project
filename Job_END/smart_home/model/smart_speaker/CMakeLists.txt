cmake_minimum_required(VERSION 3.16)
project(smart_speaker)

set(CMAKE_CXX_STANDARD 23)

add_library(smart_speaker STATIC source/smart_speaker.cpp)

target_include_directories(smart_speaker PUBLIC include)

target_link_libraries(smart_speaker PUBLIC device room isensor_device iactive_device)