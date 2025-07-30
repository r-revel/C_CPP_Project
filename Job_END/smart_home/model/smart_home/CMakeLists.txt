cmake_minimum_required(VERSION 3.16)
project(smart_home)

set(CMAKE_CXX_STANDARD 23)

add_library(smart_home STATIC source/smart_home.cpp)

target_include_directories(smart_home PUBLIC include)

target_link_libraries(smart_home PUBLIC smart_speaker)