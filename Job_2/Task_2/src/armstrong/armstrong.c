#include <stdbool.h>
#include "armstrong.h"

bool IsArmstrongNumberWithStatus(unsigned int number, Status *isStatus)
{
  unsigned int originalNum;
  unsigned int remainder;
  unsigned int n = 0;
  unsigned int result = 0;

  originalNum = number;

  // Подсчитываем количество цифр в числе:
  while (originalNum != 0)
  {
    originalNum /= 10;
    ++n;
  }

  originalNum = number;

  // Вычисляем сумму цифр, возведенных в степень n:
  while (originalNum != 0)
  {
    remainder = originalNum % 10;

    unsigned int power = 1;
    for (unsigned int i = 0; i < n; i++)
    {
      power *= remainder;
    }

    result += power;
    originalNum /= 10;
  }

  if (result == number)
  {
    *isStatus = IsArmstrong;
  }
  else
  {
    *isStatus = NotArmstrong;
  }

  return result == number;
}

bool IsArmstrongNumberSimple(unsigned int number)
{
  Status _; // Как будто не лучший способ
  return  IsArmstrongNumberWithStatus(number, &_);
}
