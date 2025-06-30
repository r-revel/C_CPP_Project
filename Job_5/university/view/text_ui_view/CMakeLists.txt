cmake_minimum_required(VERSION 3.16)
project (text_ui_view)

set(CMAKE_CXX_STANDARD 23)

add_library(text_ui_view STATIC source/text_ui_view.cpp)

target_include_directories(text_ui_view PUBLIC include)
target_link_libraries(text_ui_view PUBLIC view ${CURSES_LIBRARY})