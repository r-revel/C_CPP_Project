#!/bin/bash

# Создаем директорию для сборки
mkdir -p build
cd build

# Генерируем файлы сборки с помощью CMake
cmake ..

# Собираем проект
make -j$(nproc)

# # Запускаем приложение
# ./application/smart_home_app