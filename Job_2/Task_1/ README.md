Вот сокращённая инструкция для Linux:

### 1. Структура проекта
```
project/
├── Makefile
├── README.md
├── src/
│   ├── main.c
│   └── armstrong/
│       ├── armstrong.c
│       └── armstrong.h
```

### 2. Сборка и запуск
```bash
# В корне проекта:
make

# Очистка
make clean
```

Если возникнут проблемы с правами:
```bash
chmod +x armstrong_program
```

Далее запускаем
```bash
./armstrong_program
```