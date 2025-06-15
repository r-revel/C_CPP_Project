cmake_minimum_required(VERSION 3.20)

project(prog4)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


find_path(READLINE_INCLUDE_DIR readline/readline.h)
find_library(READLINE_LIBRARY NAMES readline)

if(NOT READLINE_INCLUDE_DIR OR NOT READLINE_LIBRARY)
    message(FATAL_ERROR "Readline library not found")
endif()

add_executable(prog4
    src/main.c
    src/armstrong/armstrong.c
    src/string_processor/string_processor.c
    src/sumnumber/sumnumber.c
)

target_include_directories(prog4 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/armstrong
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_processor
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sumnumber
    ${READLINE_INCLUDE_DIR}
)


target_link_libraries(prog4 PRIVATE ${READLINE_LIBRARY} history)