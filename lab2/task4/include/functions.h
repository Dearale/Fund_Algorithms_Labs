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


int convertFromRim(int *num, const char * input);

int fromZeckendorf(unsigned int *num, const char *input);

int convertToBase10(const char *input, int base, int * number, bool isCapital);
#endif