#ifndef ARMSTRONG_H
#define ARMSTRONG_H

#include <stdbool.h> 

typedef enum status { 
  IsArmstrong = 1, 
  NotArmstrong = 0, 
  error = -1 
} Status;



// Проверяет, без поля status
bool IsArmstrongNumberSimple(unsigned int number);

// Проверяет, является ли число числом Армстронга
bool IsArmstrongNumberWithStatus(unsigned int number, Status *isStatus);


#endif // ARMSTRONG_H