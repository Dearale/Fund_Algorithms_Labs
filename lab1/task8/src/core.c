#include "../include/core.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

bool convertToBase10(char word[], int base, long long * number, int startIndex) {
    *number = 0;
    for (int i = startIndex; word[i] != '\0'; i++)
    {
        int num = word[i] - '0';
        if (word[i] >= 'a') {
            num = word[i] - 'a' + 10;
        }
        if ((LLONG_MAX - num) / base < *number) {
            return false;
        }

        *number = *number * base + num;
    }

    return true;
}

void reverseString(char word[]) {
    int length = strlen(word);
    int left = 0;
    int right = length - 1;
    while (left < right) {
        char tmp = word[left];
        word[left] = word[right];
        word[right] = tmp;

        left++;
        right--;
    }
}

void convertFromBase10To(int base, long long number, char word[]) {
    if (number == 0) {
        word[0] = '0';
        word[1] = '\0';
        return;
    }
    int i = 0;
    while (number > 0) {
        int digit = number % base;
        number /= base;
        int curChar;
        if (digit <= 9) {
            curChar = digit + '0';
        } else {
            curChar = (digit - 10) + 'a';
        }
        word[i] = curChar;
        i++;
    }
    word[i] = '\0';
    reverseString(word);
}

void processCharacter(char word[], int i, int *startIndex, bool *containsLeadingZeros, 
                        int maxValInBase, int * length, bool *isValidNumber, int base) {
    if (*startIndex == i && word[i] == '0') {
        *containsLeadingZeros = true;
        (*startIndex)++;
        return;
    }
    if (base <= 9) {
        if (!('0' <= word[i] && word[i] <= maxValInBase)) {
            *isValidNumber = false;
            return;
        }
    } else {
        if (!(('0' <= word[i] && word[i] <= '9') || ('a' <= word[i] && word[i] <= maxValInBase))) {
            *isValidNumber = false;
            return;
        }
    }
    *length = i - *startIndex + 1;
}

void processWord(char word[], int base, char maxValInBase, long long * maxNum, bool * isMaxNumPositive, bool * atLeastOneNumHasBeenGiven) {
    bool isValidNumber = true;
    bool isPositive = true;
    int startIndex = 0;
    bool containsLeadingZeros = false;
    if (word[0] == '-'){
        isPositive = false;
        startIndex = 1;
    } else if (word[0] == '+') {
        startIndex = 1;
    }
    int length = 0;
    for (int i = startIndex; word[i] != '\0'; i++)
    {
        processCharacter(word, i, &startIndex, &containsLeadingZeros, maxValInBase, &length, &isValidNumber, base);
    }
    if (length == 0) {
        if (containsLeadingZeros) {
            length = 1;
            startIndex--;
        } else {
            isValidNumber = false;
        }
    }
    word[startIndex + length] = '\0';
    if (isValidNumber) {
        long long number = 0;
        
        if (convertToBase10(word, base, &number, startIndex)) {
            if (number > *maxNum) {
                *maxNum = number;
                *isMaxNumPositive = isPositive;
            }
        }
        *atLeastOneNumHasBeenGiven = true;
    }
}
