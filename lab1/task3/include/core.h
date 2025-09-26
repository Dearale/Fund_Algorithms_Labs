#ifndef CORE_H
#define CORE_H
#include "statusManager.h"
#include <stdbool.h>

void printEquationSolution(double a, double b, double c);

bool isEqualDouble(double a, double b, double eps);

bool isEqualZero(double a, double eps);

Status printEquationSolutions(double inputVals[]);

Status printIsFirstMultipleOfSecond(long a, long b);

Status printCanBeRightTriangle(double inputVals[4]);


#endif