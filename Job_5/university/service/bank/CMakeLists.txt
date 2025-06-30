cmake_minimum_required(VERSION 3.16)
project (banking_service)

set(CMAKE_CXX_STANDARD 23)

add_library(banking_service STATIC source/banking_service.cpp)

target_include_directories(banking_service PUBLIC include)
target_link_libraries(banking_service PUBLIC account account_repository)