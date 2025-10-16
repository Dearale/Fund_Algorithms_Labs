#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/demonstration.h"
#include "../include/core.h"


void test_Ro_sprintf() {
    char arr[256];
    int inputs[] = {1, 2, 4, 3888, 3999};
    size_t n = sizeof(inputs) / sizeof(inputs[0]);

    printf("[Тест %%Ro — Римские числа]\n");
    for (size_t i = 0; i < n; i++) {
        oversprintf(arr, "%Ro", inputs[i]);
        printf("Вход %d → %s\n", inputs[i], arr);
    }
    printf("\n");
}

void test_Zr_sprintf() {
    char arr[256];
    unsigned int uinput;

    printf("[Тест %%Zr — Цекендорфово представление]\n");

    unsigned int inputs[] = {128, 1, 0, 34, UINT_MAX};
    size_t n = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < n; i++) {
        uinput = inputs[i];
        oversprintf(arr, "%Zr", uinput);
        printf("Вход %u → %s\n", uinput, arr);
    }
    printf("\n");
}

void test_Cv_CV_sprintf() {
    char arr[256];
    int input, base;

    printf("[Тест %%Cv — перевод десятичную СС в другую, маленькие буквы]]\n");
    int tests[][2] = {
        {1, 2}, {2, 2}, {25, 37}, {25, 36}, {255, 16}
    };
    for (int i = 0; i < 5; i++) {
        input = tests[i][0];
        base = tests[i][1];
        oversprintf(arr, "%Cv", input, base);
        printf("Вход %d, основание %d → %s\n", input, base, arr);
    }
    printf("\n");

    printf("[Тест %%CV — перевод десятичную СС в другую, большие буквы]\n");
    for (int i = 0; i < 5; i++) {
        input = tests[i][0];
        base = tests[i][1];
        oversprintf(arr, "%CV", input, base);
        printf("Вход %d, основание %d → %s\n", input, base, arr);
    }
    printf("\n");
}

void test_to_TO_sprintf() {
    char arr[256];
    const char *inputs[] = {"abc", "56", "zzz", "abc", "ff"};
    int bases[] = {15, 37, 36, 2, 16};

    printf("[Тест %%to — перевод СС в десятичную, маленькие буквы]]\n");
    for (int i = 0; i < 5; i++) {
        oversprintf(arr, "%to", inputs[i], bases[i]);
        printf("Вход \"%s\" (основание %d) → %s\n", inputs[i], bases[i], arr);
    }
    printf("\n");

    const char *inputsU[] = {"ABC", "56", "ZZZ", "ABC", "FF"};
    int basesU[] = {15, 37, 36, 2, 16};

    printf("[Тест %%TO — перевод СС в десятичную, большие буквы]\n");
    for (int i = 0; i < 5; i++) {
        oversprintf(arr, "%TO", inputsU[i], basesU[i]);
        printf("Вход \"%s\" (основание %d) → %s\n", inputsU[i], basesU[i], arr);
    }
    printf("\n");
}

void test_memory_dumps_sprintf() {
    char arr[256];
    printf("[Тест %%mi — дамп памяти int]\n");
    int ints[] = {256, 259, -1};
    for (int i = 0; i < 3; i++) {
        oversprintf(arr, "%mi", ints[i]);
        printf("int %d → %s\n", ints[i], arr);
    }
    printf("\n");

    printf("[Тест %%mu — дамп памяти unsigned int]\n");
    unsigned int uints[] = {256, 259, 1};
    for (int i = 0; i < 3; i++) {
        oversprintf(arr, "%mu", uints[i]);
        printf("unsigned %u → %s\n", uints[i], arr);
    }
    printf("\n");

    printf("[Тест %%md — дамп памяти double]\n");
    double doubles[] = {1.5423, -45634.3, 1.0};
    for (int i = 0; i < 3; i++) {
        oversprintf(arr, "%md", doubles[i]);
        printf("double %.6lf → %s\n", doubles[i], arr);
    }
    printf("\n");

    printf("[Тест %%mf — дамп памяти float]\n");
    float floats[] = {1.5423f, -45634.3f, 1.0f};
    for (int i = 0; i < 3; i++) {
        oversprintf(arr, "%mf", floats[i]);
        printf("float %.4f → %s\n", floats[i], arr);
    }
    printf("\n");
}


void test_Ro_fprintf() {
    printf("[Тест %%Ro — римские цифры]\n");
    int inputs[] = {1, 2, 4, 3888, 3999};
    size_t n = sizeof(inputs) / sizeof(inputs[0]);
    for (size_t i = 0; i < n; i++) {
        overfprintf(stdout, "Вход %d → %Ro\n", inputs[i], inputs[i]);
    }
    printf("\n");
}

void test_Zr_fprintf() {
    printf("[Тест %%Zr — цекендорфово представление]\n");
    unsigned int inputs[] = {128, 1, 0, 34, UINT_MAX};
    size_t n = sizeof(inputs) / sizeof(inputs[0]);
    for (size_t i = 0; i < n; i++) {
        overfprintf(stdout, "Вход %u → %Zr\n", inputs[i], inputs[i]);
    }
    printf("\n");
}

void test_Cv_CV_fprintf() {
    printf("[Тест %%Cv — перевод десятичную СС в другую, маленькие буквы]\n");
    int tests[][2] = {
        {1, 2}, {2, 2}, {25, 37}, {25, 36}, {255, 16}
    };
    for (int i = 0; i < 5; i++) {
        overfprintf(stdout, "Число %d, основание %d → %Cv\n",
                    tests[i][0], tests[i][1], tests[i][0], tests[i][1]);
    }
    printf("\n");

    printf("[Тест %%CV — перевод десятичную СС в другую, большие буквы]\n");
    for (int i = 0; i < 5; i++) {
        overfprintf(stdout, "Число %d, основание %d → %CV\n",
                    tests[i][0], tests[i][1], tests[i][0], tests[i][1]);
    }
    printf("\n");
}

void test_to_TO_fprintf() {
    printf("[Тест %%to — перевод СС в десятичную, маленькие буквы]\n");
    const char *inputs[] = {"abc", "56", "zzz", "abc", "ff"};
    int bases[] = {15, 37, 36, 2, 16};
    for (int i = 0; i < 5; i++) {
        overfprintf(stdout, "Строка \"%s\", основание %d → %to\n",
                    inputs[i], bases[i], inputs[i], bases[i]);
    }
    printf("\n");

    printf("[Тест %%TO — перевод СС в десятичную, большие буквы]\n");
    const char *inputsU[] = {"ABC", "56", "ZZZ", "ABC", "FF"};
    int basesU[] = {15, 37, 36, 2, 16};
    for (int i = 0; i < 5; i++) {
        overfprintf(stdout, "Строка \"%s\", основание %d → %TO\n",
                    inputsU[i], basesU[i], inputsU[i], basesU[i]);
    }
    printf("\n");
}

void test_memory_dumps_fprintf() {
    printf("[Тест %%mi — дамп памяти int]\n");
    int ints[] = {256, 259, -1};
    for (int i = 0; i < 3; i++) {
        overfprintf(stdout, "int %d → %mi\n", ints[i], ints[i]);
    }
    printf("\n");

    printf("[Тест %%mu — дамп памяти unsigned int]\n");
    unsigned int uints[] = {256, 259, 1};
    for (int i = 0; i < 3; i++) {
        overfprintf(stdout, "unsigned %u → %mu\n", uints[i], uints[i]);
    }
    printf("\n");

    printf("[Тест %%md — дамп памяти double]\n");
    double doubles[] = {1.5423, -45634.3, 1.0};
    for (int i = 0; i < 3; i++) {
        overfprintf(stdout, "double %.6lf → %md\n", doubles[i], doubles[i]);
    }
    printf("\n");

    printf("[Тест %%mf — дамп памяти float]\n");
    float floats[] = {1.5423f, -45634.3f, 1.0f};
    for (int i = 0; i < 3; i++) {
        overfprintf(stdout, "float %.4f → %mf\n", floats[i], floats[i]);
    }
    printf("\n");
}

void printTestsForFprintf() {
    printf("Тесты overfprintf\n\n");
    FILE *fout = fopen("output.txt", "w");

    printf("[Комбинированный пример Для числа 5]\n");
    overfprintf(stdout, "Zr: %Zr | lld: %lld | Ro: %Ro\n", 5, 5LL, 5);
    printf("\n");

    test_Ro_fprintf();
    test_Zr_fprintf();
    test_Cv_CV_fprintf();
    test_to_TO_fprintf();
    test_memory_dumps_fprintf();

    if (fout) {
        overfprintf(fout, "Пример записи в файл: 9, 9, (255, 16) %Ro, %Zr, %Cv\n", 9, 9u, 255, 16);
        fclose(fout);
        printf("Результаты также записаны в файл output.txt\n");
    }

    printf("Конец тестов overfprintf\n\n");
}

void printTestsForSprintf() {
    printf("Тесты oversprintf\n\n");
    test_Ro_sprintf();
    test_Zr_sprintf();
    test_Cv_CV_sprintf();
    test_to_TO_sprintf();
    test_memory_dumps_sprintf();
    printf("Конец тестов oversprintf\n\n");
}

void demonstrate() {
    printTestsForSprintf();
    printTestsForFprintf();
}