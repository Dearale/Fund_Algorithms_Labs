#ifndef CORE_H
#define CORE_H

#include <stdbool.h>


bool convertToBase10(char word[], int base, long long * number, int startIndex);

void reverseString(char word[]);

void convertFromBase10To(int base, long long number, char word[]);

void processWord(char word[], int base, char maxValInBase, long long * maxNum, bool * isMaxNumPositive, bool * atLeastOneNumHasBeenGiven);

#endif