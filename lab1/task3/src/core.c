#include <../include/core.h>
#include "../include/statusManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


void printEquationSolution(double a, double b, double c) {
    printf("Для a = %g, b = %g, c = %g: ", a, b, c);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("решением являются любые числа\n");
            } else {
                printf("решений нет\n");
            }
        } else {
            double x = -c / b;
            printf("x = %g\n", x);
        }
    } else {
        double d = b * b - 4 * a * c;
        if (d < 0) {
            printf("решений нет\n");
        } else if (d == 0) {
            double x = -b / (2 * a);
            printf("x = %g\n", x);
        } else {
            double dSqr = sqrt(d);
            double x1 = (-b - dSqr) / (2 * a);
            double x2 = (-b + dSqr) / (2 * a);
            printf("x1 = %g, x2 = %g\n", x1, x2);

        }
    }
}

bool isEqualDouble(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

bool isEqualZero(double a, double eps) {
    return fabs(a) < eps;
}

Status printEquationSolutions(double inputVals[]) {
    double e = inputVals[0];
    if (e <= 0) {
        return INCORRECT_EPSILON;
    }
    double a = inputVals[1];
    double b = inputVals[2];
    double c = inputVals[3];
    printEquationSolution(a, b, c);
    if (!isEqualDouble(b, c, e)) {
        printEquationSolution(a, c, b);
    }
    if (!isEqualDouble(a, b, e)) {
        printEquationSolution(b, a, c);
        if (!isEqualDouble(a, c, e)) {
            printEquationSolution(b, c, a);
        }
    }
    if (!isEqualDouble(b, c, e) && !isEqualDouble(a, c, e)) {
        printEquationSolution(c, a, b);
        if (!isEqualDouble(a, b, e)) {
            printEquationSolution(c, b, a);
        }
    }
    return OK;
}


Status printIsFirstMultipleOfSecond(long a, long b) {
    if (a == 0 || b == 0) {
        return NO_ZEROS_FOR_MULTIPLES;
    }

    if (a % b == 0) {
        printf("Число %ld кратно числу %ld\n", a, b);
    } else {
        printf("Число %ld не кратно числу %ld\n", a, b);
    }
    return OK;
}

Status printCanBeRightTriangle(double inputVals[4]) {
    double e = inputVals[0];
    if (e <= 0) {
        return INCORRECT_EPSILON;
    }
    double a = inputVals[1];
    double b = inputVals[2];
    double c = inputVals[3];
    printf("a = %g, b = %g, c = %g ", a, b, c);

    bool canBeRightTriangle = true;
    if (isEqualZero(a, e) || isEqualZero(b, e) || isEqualZero(c, e)) {
        canBeRightTriangle = false;
    } else if (
        !isEqualDouble(a * a + b * b, c * c, e) &&
        !isEqualDouble(a * a + c * c, b * b, e) &&
        !isEqualDouble(b * b + c * c, a * a, e)
    ) {
        canBeRightTriangle = false;
    }

    if (!canBeRightTriangle) {
        printf("не ");
    }
    printf("могут являться сторонами прямоугольного треугольника\n");
    return OK;
}
