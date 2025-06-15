cmake_minimum_required(VERSION 3.20)
project(geometry CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Находим GTest
find_package(GTest REQUIRED)

# Сначала создаем статическую библиотеку с основными классами
add_library(geometry_lib STATIC
    src/point/point.cpp
    src/figure/figure.cpp
)

# Указываем пути к заголовочным файлам
target_include_directories(geometry_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/point
    ${CMAKE_CURRENT_SOURCE_DIR}/src/figure
)

# Основное приложение
add_executable(geometry_app src/main.cpp)
target_link_libraries(geometry_app geometry_lib)

# Тесты
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    
    add_executable(geometry_tests
        tests/test_point.cpp
        tests/test_figure.cpp
    )
    
    # Подключаем библиотеку и GTest к тестам
    target_link_libraries(geometry_tests
        geometry_lib
        GTest::GTest
        GTest::Main
    )
    
    add_test(NAME geometry_tests COMMAND geometry_tests)
endif()