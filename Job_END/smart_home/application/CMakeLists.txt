cmake_minimum_required(VERSION 3.16)
project(smart_home_app)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск библиотек
find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

# main.cpp
add_executable(smart_home_app source/main.cpp)

# Подключаем include-директорию
target_include_directories(smart_home_app PUBLIC include)

# Линковка
target_link_libraries(
    smart_home_app
    PUBLIC
    cli_view
    thermometer
    smart_bulb
    smart_kettle
    leak_sensor
    air_conditioner
    room
    smart_speaker
    smart_home
    device_controller
    smart_home_controller
    smart_home_cli
    ${CMAKE_THREAD_LIBS_INIT}
    ${CURSES_LIBRARIES}
)