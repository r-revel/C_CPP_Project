cmake_minimum_required(VERSION 3.16)
project (text_ui_controller)

set(CMAKE_CXX_STANDARD 23)

add_library(text_ui_controller STATIC source/text_ui_controller.cpp)

target_include_directories(text_ui_controller PUBLIC include)
target_link_libraries(text_ui_controller PUBLIC controller text_ui_view debit_account credit_account saving_account ${CURSES_LIBRARY})



