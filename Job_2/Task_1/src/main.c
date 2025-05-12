#include <stdio.h>
#include "armstrong/armstrong.h"

int main() {
    Status status;
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    if (IsArmstrongNumber(num, &status))  {
       printf("%d — это число Армстронга!\n", num);
    } else if (status == NotArmstrong) {
       printf("%d — это НЕ число Армстронга.\n", num);
    } else {
      printf("Ошибка ввода\n");
    }
    return status;
}