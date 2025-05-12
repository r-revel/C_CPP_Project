#ifndef ARMSTRONG_H
#define ARMSTRONG_H

#include <stdbool.h> 

typedef enum status { 
  IsArmstrong = 1, 
  NotArmstrong = 0, 
  error = -1 
} Status;

// Проверяет, является ли число числом Армстронга
bool IsArmstrongNumber(unsigned long long number, Status *isStatus);

#endif