#include <stdbool.h>
#include "sumnumber.h"

bool IsSumNumber(unsigned int number, unsigned int n)
{
  unsigned int originalNum;
  unsigned int remainder;
  unsigned int result = 0;

 originalNum = number;

  while (originalNum != 0)
  {
    result += originalNum % 10;
    originalNum /= 10;
  }

  return result > n;
}