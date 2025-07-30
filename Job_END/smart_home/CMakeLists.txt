cmake_minimum_required(VERSION 3.16)
project (smart_home_system)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Находим необходимые библиотеки
find_package(PkgConfig REQUIRED)
find_package(Curses REQUIRED)

# Добавление поддиректорий
add_subdirectory(model)
# add_subdirectory(repossitory)
# add_subdirectory(service)
# add_subdirectory(controller)
add_subdirectory(view)
add_subdirectory(application)