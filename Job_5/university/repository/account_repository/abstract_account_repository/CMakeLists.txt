cmake_minimum_required(VERSION 3.16)
project(account_repository)

set(CMAKE_CXX_STANDARD 23)

add_library(account_repository INTERFACE)

target_include_directories(account_repository INTERFACE include)
target_link_libraries(account_repository INTERFACE account)