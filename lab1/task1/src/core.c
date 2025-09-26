#include "../include/core.h"
#include "../include/statusManager.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

Status printNaturals(const int x) {
    if (x == 0) {
        return DIVISION_BY_ZERO;
    }
    printf("Числа, кратные %d от 1 до 100: ", x);
    int atLeastOneExists = 0;
    for (size_t i = 1; i <= 100; i++)
    {
        if (i % x == 0) {
            printf("%ld ", i);
            atLeastOneExists = 1;
        }
    }
    if (!atLeastOneExists) {
        printf("отсутствуют");
    }
    printf("\n");
    return OK;
}

Status printIsPrimeOrComposite(const int x) {
    printf("Число %d ", x);
    if (x < 2) {
        printf("не является простым или составным.\n");
        return OK;
    }

    for (int i = 2; i <= (int)sqrt(x); i++)
    {
        if (x % i == 0) {
            printf("является составным.\n");
            return OK;
        }
    }
    
    printf("является простым.\n");
    return OK;
}

Status printIn16NumSystem(int x) {
    if (x == 0) {
        printf("Число в 16-ричной системе: 0\n");
        return OK;
    }

    char res[10];
    int length = 0;
    while (x > 0)
    {
        int left = x % 16;
        x /= 16;
        res[length++] = left < 10 ? (left + '0') : (left - 10 + 'A'); 
    }
    printf("Число в 16-ричной системе: ");
    for (int i = length - 1; i >= 0; i--)
    {
        printf("%c ", res[i]);
    }
    printf("\n");

    return OK;
}

Status printPowerTable(int x) {
    if (x < 1 || x > 10){
        return OUT_OF_BOUNDS_FOR_DEGREE_TABLE;
    }
    printf("Таблица степеней:\n");
    printf(" n |");
    for (int i = 1; i <= x; i++)
    {
        printf("         n^%d", i);
    }
    printf("\n");
    printf("-----");
    for (int i = 0; i < x; i++)
    {
        printf("------------");
    }
    
    printf("\n");
    
    for (int base = 1; base <= 10; base++)
    {
        printf("%2d | ", base);
        for (int exp = 1; exp <= x; exp++)
        {
            long long res = (long long)pow(base, exp);
            printf("%11lld ", res);
        }
        printf("\n");   
    }
    return OK;
}

Status printSumUpToX(int x) {
    if (x == 0) {
        return OUT_OF_BOUNDS_FOR_SUM_UP_TO_X;
    }
    long long xlong = (long long)x;
    long long res = xlong * (xlong + 1) / 2;
    printf("Сумма натуральных чисел от 1 до %d = %lld\n", x, res);
    return OK;
}

Status printFactorial(int x) {
    if (x > 20) {
        return OUT_OF_BOUNDS_FOR_FACTORIAL;
    }
    long long res = 1;
    for (int i = 2; i <= x; i++)
    {
        res *= i;
    }
    printf("%d! = %lld\n", x, res);
    return OK;
}

void printUsage() {
    printf("Использование: <имя программы> <неотрицательное целое число> <флаг>. Пример: \"./task1 123 -h\"\n");
}
