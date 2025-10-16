#include "../include/core.h"
#include "../include/statusManager.h"

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

Status calcNumAndDen(const double eps, const double val, long long *num, long long *den) {
    double fraq = val;
    long long nPrev = 1, dPrev = 0;
    long long nPrevPrev = 0, dPrevPrev = 1;
    long long n, d;

    do {
        long long b_i = (long long)floor(fraq);

        if (b_i != 0 && (nPrev > LLONG_MAX / b_i || dPrev > LLONG_MAX / b_i))
            return NUMBER_OUT_OF_BOUNDS;

        n = b_i * nPrev + nPrevPrev;
        d = b_i * dPrev + dPrevPrev;

        double aprx = (double)n / d;
        if (fabs(aprx - fraq) < eps)
            break;

        nPrevPrev = nPrev;
        dPrevPrev = dPrev;
        nPrev = n;
        dPrev = d;

        double fraqPart = fraq - b_i;
        if (fabs(fraqPart) < eps)
            break;
        
        fraq = 1.0 / fraqPart;
    } while(true);

    *num = n;
    *den = d;

    return OK;
}

Status hasFiniteRepresentation(bool * res, int base, double val) {
    if (base < 2) {
        return BASE_OUT_OF_BOUNDS;
    }
    if (val <= EPSILON || val >= 1 - EPSILON) {
        return NUMBER_OUT_OF_BOUNDS;
    }
    long long num = 0;
    long long den = 0;
    Status status = calcNumAndDen(EPSILON, val, &num, &den);
    if (status != OK) {
        return NUMBER_OUT_OF_BOUNDS;
    }

    long long g = gcd(num, den);
    den /= g;

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