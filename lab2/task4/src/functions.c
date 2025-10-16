#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../include/functions.h"


const char toRim[] = "MDCLXVI";
const int rimVals[] = {1000, 500, 100, 50, 10, 5, 1};

int getIndexFromRimChar(char c) {
    for (size_t i = 0; i < strlen(toRim); i++)
    {
        if (toupper((unsigned char)c) == toRim[i]) {
            return i;
        }
    }

    return -1;
}

int convertFromRim(int * num, const char * input)
{
    *num = 0;
    const char * ip = input;
    int res = 0;
    while (*ip && isspace((unsigned char)*ip)) {
        ip++;
    }
    if (*ip == '\0') {
        return 0;
    }
    
    int index = getIndexFromRimChar(*ip);
    if (index < 0) {
        return 0;
    }
    int prevValue = rimVals[index];
    ip++;

    while (*ip && !isspace((unsigned char)*ip)) {
        index = getIndexFromRimChar(*ip);
        if (index < 0) {
            return 0;
        }
        
        int curValue = rimVals[index];

        if (curValue > prevValue) {
            res -= prevValue;
        } else {
            res += prevValue;
        }

        prevValue = curValue;
        ip++;
    }
    
    res += prevValue;
    *num = res;
    return ip - input;
}

void generateFibonacci(unsigned int * fib, int *count)
{
    fib[0] = 1;
    fib[1] = 2;

    *count = 2;
    while (true)
    {
        if (fib[*count - 1] > UINT_MAX - fib[*count - 2])
        {
            break;
        }
        
        fib[*count] = fib[*count - 1] + fib[*count - 2];
        (*count)++;
    }
}

void printFibonacci(unsigned int *fib, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%u ", fib[i]);
    }
}

int fromZeckendorf(unsigned int * num, const char *input)
{
    const char * ip = input;

    unsigned int fib[MAX_ZECKENDORF_LEN];
    int count = 0;
    generateFibonacci(fib, &count);

    unsigned int res = 0;

    while (*ip && isspace((unsigned char)*ip)) {
        ip++;
    }

    const char * start = ip;
    while (*ip && !isspace((unsigned char)*ip)) {
        if (*ip == '1' && ip[1] && !isspace((unsigned char)ip[1])) {
            res += fib[ip - start];
            // printf("ip - start: %ld\n", ip - start);
        }
        ip++;
    }

    *num = res;

    return ip - input;
}

bool isValidCharForBase(const char c, int base, bool isCapital)
{
    bool isValid = false;
    char startLetter = isCapital ? 'A' : 'a';
    if (base >= MIN_BASE && base <= MAX_BASE)
    {
        isValid = '0' <= c && c <= (base - 1 + '0');

        if (base >= 11)
        {
            isValid = isValid || (startLetter <= c && c <= (base - 11 + startLetter));
        }
    }
    return isValid;
}

int convertToBase10(const char *input, int base, int * number, bool isCapital) {
    if (base < MIN_BASE || base > MAX_BASE)
    {
        base = 10;
    }

    const char *word = input;
    while (*word && isspace((unsigned char)*word)) {
        word++;
    }

    int startIndex = 0;
    int isPositive = true;
    char startLetter = isCapital ? 'A' : 'a';
    if (word[0] == '+' || word[0] == '-')
    {
        startIndex = 1;
        isPositive = (word[0] == '+');
    }

    *number = 0;
    int i = startIndex;
    for (; word[i] != '\0' && !isspace((unsigned char)word[i]); i++)
    {
        if (!isValidCharForBase(word[i], base, isCapital))
        {
            *number = 0;
            return word + i - input;
        }

        int num = word[i] - '0';
        if (word[i] >= startLetter) {
            num = word[i] - startLetter + 10;
        }
        if ((INT_MAX - num) / base < *number) {
            *number = 0;
            return word + i - input;
        }

        *number = *number * base + num;
    }
    if (!isPositive)
    {
        *number = -(*number);
    }

    return word + i - input;
}