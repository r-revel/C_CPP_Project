#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "armstrong.h"
#include "string_processor.h"
#include "sumnumber.h"

static int* extract_numbers(const char* str, int* count) {
    int capacity = 10;
    int* numbers = malloc(capacity * sizeof(int));
    *count = 0;
    
    const char* p = str;
    while (*p) {
        if (isdigit(*p) || (*p == '-' && isdigit(*(p+1)))) {
            int num = strtol(p, (char**)&p, 10);
            
            if (*count >= capacity) {
                capacity *= 2;
                numbers = realloc(numbers, capacity * sizeof(int));
            }
            
            numbers[(*count)++] = num;
        } else {
            p++;
        }
    }
    
    return numbers;
}

static int* filter_and_duplicate(int* numbers, int* count, int n) {
    // Фильтрация чисел по сумме цифр
    int filtered_count = 0;
    for (int i = 0; i < *count; i++) {
        if (IsSumNumber(numbers[i], n)) {
            numbers[filtered_count++] = numbers[i];
        }
    }
    *count = filtered_count;
    
    // Дублирование чисел Армстронга
    int new_count = *count;
    for (int i = 0; i < new_count; i++) {
        if (IsArmstrongNumberSimple(numbers[i])) {
            numbers = realloc(numbers, (new_count + 1) * sizeof(int));
            memmove(numbers + i + 2, numbers + i + 1, (new_count - i - 1) * sizeof(int));
            numbers[i + 1] = numbers[i];
            new_count++;
            i++;
        }
    }
    *count = new_count;
    
    return numbers;
}

char* process_string(const char* input, int n) {
    int count = 0;
    int* numbers = extract_numbers(input, &count);
    numbers = filter_and_duplicate(numbers, &count, n);
    
    // Вычисляем необходимый размер строки
    int length = 0;
    for (int i = 0; i < count; i++) {
        char buf[32];
        length += snprintf(buf, sizeof(buf), "%d ", numbers[i]);
    }
    
    // Формируем строку результата
    char* result = malloc(length + 1);
    char* p = result;
    for (int i = 0; i < count; i++) {
        p += sprintf(p, "%d", numbers[i]);
        if (i < count - 1) {
            *p++ = ' ';
        }
    }
    *p = '\0';
    
    free(numbers);
    return result;
}