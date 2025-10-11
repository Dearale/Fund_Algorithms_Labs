#include "../include/core.h"
#include "../include/statusManager.h"

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_DENOMINATOR 1e12
#define EPSILON (1 / MAX_DENOMINATOR)

long long gcd(long long a, long long b) {
    long long tmp = 0;
    while (b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

Status hasFiniteRepresentation(bool * res, int base, double val) {
    if (base < 2) {
        return BASE_OUT_OF_BOUNDS;
    }
    if (val <= EPSILON || val >= 1 - EPSILON) {
        return NUMBER_OUT_OF_BOUNDS;
    }

    double scaled = val * MAX_DENOMINATOR;
    long long num = llround(scaled);
    long long g = gcd(num, MAX_DENOMINATOR);
    num /= g;
    long long den = MAX_DENOMINATOR / g;

    while (den > 1) {
        g = gcd(den, base);
        if (g == 1)
            break;
        den /= g;
    }

    *res = (den == 1);
    return OK;
}

Status haveFiniteRepresentations(bool ** res, int base, int count, ...) {
    *res = (bool *)malloc(count * sizeof(bool));
    if (*res == NULL) {
        return MEMORY_ERROR;
    }
    
    va_list args;
    va_start(args, count);
    
    double val = 0;
    
    for (int i = 0; i < count; i++)
    {
        val = va_arg(args, double);
        bool curRes = false;
        Status status = hasFiniteRepresentation(&curRes, base, val);
        if (status != OK) {
            va_end(args);
            return status;
        }
        (*res)[i] = curRes;
    }
    
    
    va_end(args);
    return OK;
}