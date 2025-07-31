cmake_minimum_required(VERSION 3.16)
project(smart_home_cli)

set(CMAKE_CXX_STANDARD 23)

add_library(smart_home_cli STATIC source/smart_home_cli.cpp)

target_include_directories(smart_home_cli PUBLIC include)
target_link_libraries(smart_home_cli PUBLIC smart_home cli_view isensor_device iactive_device device_controller smart_home_controller thermometer smart_bulb smart_kettle leak_sensor air_conditioner)