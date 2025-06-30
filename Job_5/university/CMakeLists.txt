cmake_minimum_required(VERSION 3.16)
project (mvc_example)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Находим необходимые библиотеки
# find_package(jsoncpp REQUIRED)
find_package(PkgConfig REQUIRED)
# pkg_check_modules(JSONCPP jsoncpp)
find_package(Curses REQUIRED)

add_subdirectory(model)
add_subdirectory(repository)
add_subdirectory(service)
add_subdirectory(view)
add_subdirectory(controller)
add_subdirectory(application)
