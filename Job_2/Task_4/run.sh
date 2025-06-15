#!/bin/bash

# Удаляем старую сборку
rm -rf build

# Создаём папку и переходим в неё
mkdir build && cd build || exit 1

# Генерируем Makefile через CMake
if ! cmake ..; then
    echo "❌ Ошибка CMake!"
    exit 1
fi

# Собираем проект
if ! make; then
    echo "❌ Ошибка сборки!"
    exit 1
fi

# Извлекаем имя программы из CMakeLists.txt
prog_name=$(grep -oP '(?<=add_executable\()\w+(?=\s)' ../CMakeLists.txt | head -n1)

if [ -z "$prog_name" ]; then
    echo "❌ Не удалось найти add_executable в CMakeLists.txt!"
    exit 1
fi

# Даём права на выполнение (если нужно)
chmod +x "$prog_name"

# Запускаем программу
echo "🚀 Запускаем ./$prog_name..."
./"$prog_name"