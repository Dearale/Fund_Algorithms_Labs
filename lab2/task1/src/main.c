#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void printRes(bool * res, int count) {
    for (int i = 0; i < count; i++)
    {
        if (res[i]) {
            printf("Число args[%d] имеет конечное представление\n", i);
        } else {
            printf("Число args[%d] не имеет конечное представление\n", i);
        }
    }
    
}

int main() {
    bool * res = NULL;
    int count = 5;
    Status status = haveFiniteRepresentations(&res, 3, count, 0.25, 0.2, 0.3, 0.4, 0.3333333333333333333333333333333333333333333333333333333333333333);
    if (status == OK) {
        printRes(res, count);
    }
    printStatus(status);
    free(res);
    return 0;
}