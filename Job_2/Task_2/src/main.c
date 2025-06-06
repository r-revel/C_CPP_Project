#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "armstrong/armstrong.h"
#include "sumnumber/sumnumber.h"


void ProcessArray(int** arr, int* size, int n) {
    // Удаляем числа где сумма цифр <= n
    int count = 0;
    for (int i = 0; i < *size; i++) {
        if (IsSumNumber((*arr)[i], n)) {
            (*arr)[count] = (*arr)[i];
            count++;
        }
    }
    *size = count;

    // Дублируем числа Армстронга
    for (int i = 0; i < *size; i++) {
        if (IsArmstrongNumberSimple((*arr)[i])) {
            *arr = realloc(*arr, (*size + 1) * sizeof(int));
            
            // Сдвигаем все элементы после текущего
            for (int j = *size; j > i; j--) {
                (*arr)[j] = (*arr)[j-1];
            }
            
            (*arr)[i+1] = (*arr)[i];
            (*size)++;
            i++; 
        }
    }
}

int main() {
    int n;
    char input[1000]; 
    int numbers[100];
    int count = 0; 
    

    printf("Введите элементы массива (например: 5,9,29,153): ");
    scanf("%999[^\n]", input);
    
    char *token = strtok(input, ",");
    while (token != NULL && count < 100) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    

    printf("Введите число n: ");
    scanf("%d", &n);
    
    // Создаём динамический массив нужного размера
    int *arr = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        arr[i] = numbers[i];
    }
    int size = count;
    

    ProcessArray(&arr, &size, n);

    printf("Результат обработки:\n");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("\n");
    
    free(arr);
    return 0;
}