CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I./src/armstrong 
LDFLAGS = -lm  
TARGET = armstrong_program

# Исходные файлы
SRC_DIR = src
ARMSTRONG_DIR = $(SRC_DIR)/armstrong
SRCS = $(SRC_DIR)/main.c $(ARMSTRONG_DIR)/armstrong.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean