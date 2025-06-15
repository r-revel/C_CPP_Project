
### 1. Структура проекта
```

geometry/
├── CMakeLists.txt
├── src/
│   ├── point/
│   │   ├── point.h
│   │   └── point.cpp
│   ├── figure/
│   │   ├── figure.h
│   │   └── figure.cpp
│   └── main.cpp
└── tests/
    ├── test_point.cpp
    └── test_figure.cpp


### 2. Сборка и запуск
```bash
# В корне проекта:
chmod +x run.sh
run.sh
```
Далее запускаем
```bash
cd build
./geometry_app
```