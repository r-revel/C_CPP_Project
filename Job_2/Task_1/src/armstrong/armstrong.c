#include <stdbool.h> 
#include "armstrong.h" 

bool IsArmstrongNumber(unsigned long long number, Status *isStatus) {
    unsigned long long int originalNum;
    unsigned long long int remainder;
    unsigned long long int n = 0;
    unsigned long long int result = 0;

    originalNum = number;

    // Подсчитываем количество цифр в числе:
    while (originalNum != 0) {
        originalNum /= 10;
        ++n;              
    }

    originalNum = number;

    // Вычисляем сумму цифр, возведенных в степень n:
    while (originalNum != 0) {
        remainder = originalNum % 10; 

        unsigned long long int power = 1;
        for (unsigned long long int i = 0; i < n; i++) {
            power *= remainder; 
        }

        result += power;
        originalNum /= 10;
    }

    if (result == number) {
      *isStatus = IsArmstrong;
    } else {
      *isStatus = NotArmstrong;
    }

    return result == number;
}