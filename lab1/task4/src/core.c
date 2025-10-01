#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUM_FOR_FACTORIAL 20

double calcByEq(double eps, double l, double r, double (*f)(double)) {
    double mid = 0;
    while (fabs(r - l) >= eps) {
        mid = (l + r) / 2.0;
        if (f(mid) > 0) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    return (l + r) / 2;
}

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


double funcForEByEq(double x) {
    return log(x) - 1;
}

double eByEq(double eps) {
    return calcByEq(eps, 2, 3, funcForEByEq);
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

double funcForPiByEq(double x) {
    return cos(x);
}

double piByEq(double eps) {
    return calcByEq(eps, -2, 0, funcForPiByEq) * (-2);
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

double funcForLn2ByEq(double x) {
    return exp(x) - 2;
}

double ln2ByEq(double eps) {
    return calcByEq(eps, 0, 1, funcForLn2ByEq);
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

double funcForSqrt2ByEq(double x) {
    return x * x - 2;
}

double sqrt2ByEq(double eps) {
    return calcByEq(eps, 1, 2, funcForSqrt2ByEq);
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
        if (m > MAX_NUM_FOR_FACTORIAL)
            break;
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
            cur += coef * powl(-1.0, k) * logl(factorial(k)) / k;
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
    double pi = acos(-1);
    double finalAddition = -pow(pi, 2) / 6;
    return finalAddition + cur;
}

int * populatePrimes(int count) {
    int * numbers = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i) {
        numbers[i] = 0;
    }

    for (int i = 2; i < count; ++i) {
        if (numbers[i]) {
            continue;
        }
        for (int j = i + i; j < count; j += i) {
            numbers[j] = 1;
        }
    }

    return numbers;
}

double calcGammaForEq(int t, int * primes) {
    double multiplication = 1;
    for (int i = 2; i < t; i++)
    {
        if (primes[i] == 0) {
            multiplication *= ((i - 1) / ((double)i));
        }
    }
    return log(t) * multiplication;
}

double gammaByEq(double eps) {
    int maxT = 1e6;
    int * primes = populatePrimes(maxT);

    if (!primes) {
        return -1;
    }

    double res = calcGammaForEq(maxT, primes);
    double l = 0;
    double r = 1;
    double mid;

    while (fabs(r - l) >= eps) {
        mid = (l + r) / 2;
        if (exp(-mid) - res > 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    free(primes);
    return (l + r) / 2.0;
}
