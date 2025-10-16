#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../include/functions.h"


const char toRim[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
const int rimVals[] = {1000, 500, 100, 50, 10, 5, 1};


void convertToRim(int num, char * output)
{
    if (num <= 0 || num > 3999)
    {
        output[0] = '\0';
        return;
    }
    char * ptr = output;
    for (size_t i = 0; i < ARR_LEN(toRim); i += 2)
    {
        int n = num / rimVals[i];

        if (n == 9) 
        {
            *ptr++ = toRim[i];
            *ptr++ = toRim[i - 2];
        }
        else if (n > 4 && n < 9)
        {
            *ptr++ = toRim[i - 1];
            memset(ptr, toRim[i], n - 5);
            ptr += n - 5;
        } else if (n == 4)
        {
            *ptr++ = toRim[i];
            *ptr++ = toRim[i - 1];
        } else {
            memset(ptr, toRim[i], n);
            ptr += n;
        }

        num -= n * rimVals[i];
    }
    *ptr = '\0';
}

void generateFibonacciUpToNum(const unsigned int num, unsigned int * fib, int *count)
{
    fib[0] = 1;
    fib[1] = 2;
    *count = 2;
    for (unsigned int i = 0; i <= 2; i++)
    {
        if (num == i)
        {
            *count = i;
            return;
        }
    }

    unsigned int nextVal = fib[0] + fib[1];
    do {
        fib[*count] = nextVal;
        (*count)++;
        nextVal = fib[*count - 2] + fib[*count - 1];
    } while (fib[*count - 1] <= UINT_MAX - fib[*count - 2] && nextVal <= num);
}

void printFibonacci(unsigned int *fib, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%u ", fib[i]);
    }
}

void toZeckendorf(unsigned int num, char *out)
{
    unsigned int fib[MAX_ZECKENDORF_LEN];
    int count = 0;
    generateFibonacciUpToNum(num, fib, &count);


    int i = count - 1;
    while (i >= 0)
    {
        if (fib[i] > num)
        {
            out[i] = '0';
            i--;
            continue;
        }

        out[i] = '1';
        if (i >= 1)
        {
            out[i - 1] = '0';
        }
        num -= fib[i];
        i -= 2;
    }
    
    out[count++] = '1';
    out[count] = '\0';
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

void convertFromBase10To(int base, int number, char word[], bool isCapital)
{
    if (base < MIN_BASE || base > MAX_BASE)
    {
        sprintf(word, "%d", number);
        return;
    }

    if (number == 0)
    {
        word[0] = '0';
        word[1] = '\0';
        return;
    }
    int i = 0;
    if (number < 0)
    {
        word[0] = '-';
        i++;
        number = -number;
    }

    char startLetter = isCapital ? 'A' : 'a';

    while (number > 0)
    {
        int digit = number % base;
        number /= base;
        int curChar;
        if (digit <= 9)
        {
            curChar = digit + '0';
        } else
        {
            curChar = (digit - 10) + startLetter;
        }
        word[i] = curChar;
        i++;
    }
    word[i] = '\0';
    reverseString(word);
}

bool isValidCharForBase(char c, int base, bool isCapital)
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

bool convertToBase10(char word[], int base, int * number, bool isCapital) {
    if (base < MIN_BASE || base > MAX_BASE)
    {
        base = 10;
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
    for (int i = startIndex; word[i] != '\0'; i++)
    {
        if (!isValidCharForBase(word[i], base, isCapital))
        {
            *number = 0;
            return false;
        }

        int num = word[i] - '0';
        if (word[i] >= startLetter) {
            num = word[i] - startLetter + 10;
        }
        if ((INT_MAX - num) / base < *number) {
            *number = 0;
            return false;
        }

        *number = *number * base + num;
    }

    if (!isPositive)
    {
        *number = -(*number);
    }

    return true;
}

void writeBits(unsigned char byte, char *out)
{
    for (int i = 7; i >= 0; i--)
    {
        if (byte & (1 << i))
        {
            *out++ = '1';
        } else
        {
            *out++ = '0';
        }
    }
    *out = '\0';
}

int dumpBytes(void *ptr, char *strp, size_t size)
{
    unsigned char *bytes = (unsigned char *)ptr;

    char bits[9];
    int written = 0;
    for (size_t i = 0; i < size; i++)
    {
        writeBits(bytes[i], bits);
        
        char * tail = (i < size - 1) ? " " : "";
        written += sprintf(strp + written, "%s%s", bits, tail);
    }

    return written;
}
