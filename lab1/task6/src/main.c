#include "../include/parseInput.h"
#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char * argv[]) {
    double eps = 0;
    Status status = extractEpsilonFromString(argc, argv, &eps);
    if (status != OK) {
        printStatus(status);
        return 1;
    }

    printf("Интеграл a: %lf\n", calcIntegralA(eps));
    printf("Интеграл b: %lf\n", calcIntegralB(eps));
    printf("Интеграл c: %lf\n", calcIntegralC(eps));
    printf("Интеграл d: %lf\n", calcIntegralD(eps));
}