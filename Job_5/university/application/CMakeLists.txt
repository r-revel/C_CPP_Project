cmake_minimum_required(VERSION 3.16)
project (application)

set(CMAKE_CXX_STANDARD 23)

add_library(banking_app STATIC source/banking_app.cpp)

target_include_directories(banking_app PUBLIC include)
target_link_libraries(
	banking_app PUBLIC 
	text_ui_controller 
	banking_service 
	text_ui_view 
	in_memory_account_repository 
	${CURSES_LIBRARY}
)

add_executable(banking source/main.cpp)
target_link_libraries(banking PUBLIC
	banking_app
	text_ui_controller 
	banking_service 
	text_ui_view 
	in_memory_account_repository
)