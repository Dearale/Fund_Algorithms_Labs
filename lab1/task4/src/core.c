#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

double eByLim(double eps) {
    double prev = 0;
    double cur = 0;
    long long n = 0;
    do {
        n++;
        prev = cur;
        cur = pow(1 + 1.0 / n, n);
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double eBySeries(double eps) {
    double prev = 0;
    double cur = 1;
    long long n = 0;
    long long curFact = 1;
    do {
        n++;
        prev = cur;
        curFact *= n;
        cur += 1.0 / curFact;
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double eByEq() {
    return exp(1);
}

double piByLim(double eps) {
    double prev = 0;
    double cur = 1;
    long long n = 0;
    do {
        n++;
        prev = cur;
        cur *= 16 * pow(n, 4) / (pow(2 * n * (2 * n - 1), 2));
    } while (fabs(cur - prev) >= eps * n);

    return cur / n;
}

double piBySeries(double eps) {
    double prev = 0;
    double cur = 0;
    long long n = 0;
    do {
        n++;
        prev = cur;
        cur += 4 * pow(-1, n - 1) / (2 * n - 1);
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double piByEq() {
    return acos(-1);
}

double ln2ByLim(double eps) {
    double prev = 0;
    double cur = 0;
    long long n = 0;
    do {
        n++;
        prev = cur;
        cur = n * (pow(2, 1.0 / n) - 1);
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double ln2BySeries(double eps) {
    double prev = 0;
    double cur = 0;
    long long n = 0;
    do {
        n++;
        prev = cur;
        cur += pow(-1, n - 1) / n;
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double ln2ByEq() {
    return log(2);
}

double sqrt2ByLim(double eps) {
    double prev = 0;
    double cur = -0.5;
    do {
        prev = cur;
        cur = cur - pow(cur, 2) / 2 + 1;
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double sqrt2BySeries(double eps) {
    double prev = 0;
    double cur = 1;
    long long n = 1;
    do {
        n++;
        prev = cur;
        cur *= pow(2, pow(2, -n));
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double sqrt2ByEq() {
    return sqrt(2);
}

long long factorial(long long n) {
    long long res = 1;
    for (long long i = 2; i <= n; i++)
    {
        res *= i;
    }

    return res;
}


long long multiplyFromTo(long long start, long long end) {
    long long res = 1;
    for (long long i = start; i <= end; i++)
    {
        res *= i;
    }

    return res;
}

double gammaByLim(double eps) {
    double prev = 0;
    double cur = 0;
    long long m = 1;
    do {
        m++;
        prev = cur;
        cur = 0;
        for (long long k = 1; k <= m; k++)
        {
            long long coef = 0;
            if (k >= m - k) {
                coef = multiplyFromTo(k + 1, m) / factorial(m - k);
            } else {
                coef = multiplyFromTo(m - k + 1, m) / factorial(k);
            }
            cur += coef * powl(-1, k) * logl(factorial(k)) / k;
        }
    } while (fabs(cur - prev) >= eps);
    return cur;
}

double gammaBySeries(double eps) {
    double prev_prev = 0;
    double prev = 0;
    double cur = 0;
    long long k = 1;
    do {
        k++;
        prev_prev = prev;
        prev = cur;
        long long sqrtK = (long long)sqrt(k);
        cur += (1.0 / (sqrtK * sqrtK) - 1.0 / k);
    } while (fabs(cur - prev) >= eps || fabs(prev - prev_prev) >= eps);
    double finalAddition = -pow(piByEq(), 2) / 6;
    return finalAddition + cur;
}

bool getNextPrimeLessThanTIfExists(long long t, long long *curPrime) {
    for (long long i = *curPrime + 1; i <= t; i++) {
        if (i == 1) {
            continue;
        }
        bool isPrime = true;
        for (long long j = 2; j * j <= i; j++) {
            if (i % j == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            *curPrime = i;
            return true;
        }
    }
    return false;
}

double gammaByEq(double eps) {
    double prev = 0;
    double cur = 0;
    long long t = 1;
    double curMultiplication = 1;
    long long curPrime = 0;
    do {
        t++;
        prev = cur;
        if (getNextPrimeLessThanTIfExists(t, &curPrime)) {
            curMultiplication *= (curPrime - 1) / (double)curPrime;
        }
        cur = -log(log(t) * curMultiplication);
    } while (fabs(cur - prev) >= eps);
    return cur;
}
