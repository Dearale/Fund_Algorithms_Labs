#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

double trapezoidal(double a, double b, int n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h);
    }

    return h * sum;
}

double calcIntegral(double a, double b, double eps, double (*func)(double)) {
    int n = 1;
    double prev = 0;
    double cur = trapezoidal(a, b, n, func);
    
    do {
        n *= 2;
        prev = cur;
        cur = trapezoidal(a, b, n, func);
    } while (fabs(cur - prev) >= eps);
    
    return cur;
}

double aFunc(double x) {
    if (fabs(x) < 1e-15) {
        return 1;
    }
    return log(1 + x) / x;
}

double calcIntegralA(double eps) {
    return calcIntegral(0, 1, eps, aFunc);
}

double bFunc(double x) {
    return exp(-pow(x, 2) / 2);
}

double calcIntegralB(double eps) {
    return calcIntegral(0, 1, eps, bFunc);
}

double cFunc(double x) {
    return -log(1 - x);
}


double calcIntegralC(double eps) {
    double b_cut = 1 - eps;
    if (eps > 0.1) {
        b_cut = 0.9;
    }
    double a = calcIntegral(0, b_cut, eps, cFunc);
    double tail = (1 - b_cut) * (1 - log(1 - b_cut));
    return a + tail;
}


double dFunc(double x) {
    return pow(x, x);
}


double calcIntegralD(double eps) {
    return calcIntegral(0, 1,eps, dFunc);
}
