#include "../include/core.h"

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_NUM_LENGTH 100


int main() {
    int base = 0;
    printf("Введите основание системы счисления: ");
    scanf("%d", &base);

    if (!(2 <= base && base <= 36)) {
        printf("Система счисления должна быть в диапазоне от 2 до 36 включительно\n");
        return 1;
    }

    printf("Введите числа. Напишите Stop для окончания ввода:\n");
    char word[MAX_WORD_LENGTH + 1];
    scanf("%100s", word);


    char maxValInBase;
    if (base <= 10) {
        maxValInBase = (base - 1) + '0';
    } else {
        maxValInBase = (base - 11) + 'a';
    }

    long long maxNum = 0;
    bool isMaxNumPositive = true;
    bool atLeastOneNumHasBeenGiven = false;
    while (strcmp(word, "Stop") != 0) {        
        processWord(word, base, maxValInBase, &maxNum, &isMaxNumPositive, &atLeastOneNumHasBeenGiven);
        scanf("%100s", word);
    }

    if (!atLeastOneNumHasBeenGiven) {
        printf("Не было введено валидных чисел\n");
        return 0;
    }
    printf("Исходное число: ");
    convertFromBase10To(base, maxNum, word);
    if (!isMaxNumPositive) {
        printf("-");
    }
    printf("%s\n", word);
    for (int i = 9; i <= 36; i += 9)
    {
        convertFromBase10To(i, maxNum, word);
        printf("В %d-ричной системе счисления: ", i);
        if (!isMaxNumPositive) {
            printf("-");
        }
        printf("%s\n", word);
    }
    return 0;
}