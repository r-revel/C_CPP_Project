cmake_minimum_required(VERSION 3.16)
project(in_memory_account_repository)

set(CMAKE_CXX_STANDARD 23)

add_library(in_memory_account_repository STATIC source/in_memory_account_repository.cpp)

target_include_directories(in_memory_account_repository PUBLIC include)

target_link_libraries(in_memory_account_repository PUBLIC account_repository)