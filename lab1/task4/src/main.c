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

    printf("Число e при помощи предела: %lf\n", eByLim(eps));
    printf("Число e при помощи ряда: %lf\n", eBySeries(eps));
    printf("Число e при помощи уравнения: %lf\n", eByEq());
    printf("Число Пи при помощи предела: %lf\n", piByLim(eps));
    printf("Число Пи при помощи ряда: %lf\n", piBySeries(eps));
    printf("Число Пи при помощи уравнения: %lf\n", piByEq());
    printf("Число ln 2 при помощи предела: %lf\n", ln2ByLim(eps));
    printf("Число ln 2 при помощи ряда: %lf\n", ln2BySeries(eps));
    printf("Число ln 2 при помощи уравнения: %lf\n", ln2ByEq());
    printf("Число sqrt(2) при помощи предела: %lf\n", sqrt2ByLim(eps));
    printf("Число sqrt(2) при помощи ряда: %lf\n", sqrt2BySeries(eps));
    printf("Число sqrt(2) при помощи уравнения: %lf\n", sqrt2ByEq());
    printf("Число γ при помощи предела: %lf\n", gammaByLim(eps));
    printf("Число γ при помощи ряда: %lf\n", gammaBySeries(eps));
    printf("Число γ при помощи уравнения: %lf\n", gammaByEq(eps));
}