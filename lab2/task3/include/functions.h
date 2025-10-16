#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <specifiers.h>

#define ARR_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MAX_RIM_NUM_LEN 15
#define MAX_ZECKENDORF_LEN 64
#define MAX_NUM_LEN 33
#define MIN_BASE 2
#define MAX_BASE 36


void convertToRim(int num, char * output);

void generateFibonacciUpToNum(const unsigned int num, unsigned int * fib, int *count);

void printFibonacci(unsigned int *fib, int count);
void toZeckendorf(unsigned int num, char *out);

void reverseString(char word[]);

void convertFromBase10To(int base, int number, char word[], bool isCapital);

bool isValidCharForBase(char c, int base, bool isCapital);

bool convertToBase10(char word[], int base, int * number, bool isCapital);
void writeBits(unsigned char byte, char *out);
int dumpBytes(void *ptr, char * strp, size_t size);
#endif