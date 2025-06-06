cmake_minimum_required(VERSION 3.20)

project(prog2)

add_executable(prog2
    src/main.c
    src/armstrong/armstrong.c
    src/sumnumber/sumnumber.c
)

target_include_directories(prog2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/armstrong
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sumnumber
)