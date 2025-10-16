#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/demonstration.h"
#include "../include/statusManager.h"
#include "../include/core.h"

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

void handleTest(Status status, bool **res) {
    if (status == OK) {
        printRes(*res, 4);
    }
    printStatus(status);
    free(*res);
    printf("\n");
}

void demonstrate() {
    bool *res = NULL;

    // Тест 1: основание 2 (бинарная система)
    printf("[Тест 1] base = 2, числа: 0.25, 0.2, 0.3, 0.5\n");
    handleTest(haveFiniteRepresentations(&res, 2, 4, 0.25, 0.2, 0.3, 0.5), &res);
    // Тест 2: основание 10 (десятичная система)
    printf("[Тест 2] base = 10, числа: 0.125, 0.3333, 0.5\n");
    handleTest(haveFiniteRepresentations(&res, 10, 3, 0.125, 0.3333, 0.5), &res);

    // Тест 3: основание 8 (восьмеричная система)
    printf("[Тест 3] base = 8, числа: 0.125, 0.3, 0.5\n");
    handleTest(haveFiniteRepresentations(&res, 8, 3, 0.125, 0.3, 0.5), &res);

    // Тест 4: ошибка — недопустимое основание
    printf("[Тест 4] base = 1, числа: 0.25, 0.5\n");
    handleTest(haveFiniteRepresentations(&res, 1, 2, 0.25, 0.5), &res);
}