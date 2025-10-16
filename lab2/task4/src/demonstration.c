#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/demonstration.h"
#include "../include/core.h"


void test_Ro_sscanf() {
    printf("[Тест %%Ro — чтение римских чисел из строки]\n");

    const char *inputs[] = {"I", "IV", "XII", "XL", "MCMXCIX"};
    int values[5] = {0};

    for (int i = 0; i < 5; i++) {
        oversscanf(inputs[i], "%Ro", &values[i]);
        printf("Строка \"%s\" → %d\n", inputs[i], values[i]);
    }
    printf("\n");
}

void test_Zr_sscanf() {
    printf("[Тест %%Zr — чтение цекендорфова представления из строки]\n");

    const char *inputs[] = {
        "1011",     // пример для числа 11
        "1001001",  // пример для 41
        "1",        // минимальное
        "10101001"  // произвольное
    };
    unsigned int values[4] = {0};

    for (int i = 0; i < 4; i++) {
        oversscanf(inputs[i], "%Zr", &values[i]);
        printf("Строка \"%s\" → %u\n", inputs[i], values[i]);
    }
    printf("\n");
}

void test_Cv_CV_sscanf() {
    printf("[Тест %%Cv — чтение числа в системе счисления с основанием N (строчные буквы)]\n");

    const char *inputs[] = {"111", "1a", "ff", "100"};
    int bases[] = {2, 16, 16, 8};
    int values[4] = {0};

    for (int i = 0; i < 4; i++) {
        oversscanf(inputs[i], "%Cv", &values[i], bases[i]);
        printf("Строка \"%s\" (основание %d) → %d\n", inputs[i], bases[i], values[i]);
    }
    printf("\n");

    printf("[Тест %%CV — чтение числа в системе счисления с основанием N (прописные буквы)]\n");

    const char *inputsU[] = {"1A", "FF", "ABC", "100"};
    int basesU[] = {16, 16, 16, 8};
    int valuesU[4] = {0};

    for (int i = 0; i < 4; i++) {
        oversscanf(inputsU[i], "%CV", &valuesU[i], basesU[i]);
        printf("Строка \"%s\" (основание %d) → %d\n", inputsU[i], basesU[i], valuesU[i]);
    }
    printf("\n");
}


void test_Ro_fscanf() {
    printf("[Тест %%Ro — чтение римских чисел из файла]\n");

    FILE *f = fopen("input_Ro.txt", "w+");
    fprintf(f, "I IV XII XL MCMXCIX");
    char *vals[5] = {"I", "IV", "XII", "XL", "MCMXCIX"};
    rewind(f);

    int value;
    for (size_t i = 0; i < 5; i++)
    {
        overfscanf(f, "%Ro", &value);
        printf("Считано значение(%s): %d\n", vals[i], value);
    }

    fclose(f);
    printf("\n");
}

void test_Zr_fscanf() {
    printf("[Тест %%Zr — чтение цекендорфова представления из файла]\n");

    FILE *f = fopen("input_Zr.txt", "w+");
    fprintf(f, "1011 1001001 1 10101001");
    char *vals[4] = {"1011", "1001001", "1", "10101001"};
    rewind(f);

    unsigned int value;
    for (size_t i = 0; i < 4; i++)
    {
        overfscanf(f, "%Zr", &value);
        printf("Считано значение(%s): %u\n", vals[i], value);
    }

    fclose(f);
    printf("\n");
}

void test_Cv_CV_fscanf() {
    printf("[Тест %%Cv — чтение числа в системе счисления (строчные буквы)]\n");

    FILE *f = fopen("input_Cv.txt", "w+");
    fprintf(f, "111 1a ff 100");
    rewind(f);

    int base, value;

    base = 2;
    overfscanf(f, "%Cv", &value, base); 
    printf("111 (base %d) → %d\n", base, value);
    base = 16;
    overfscanf(f, "%Cv", &value, base);
    printf("1a  (base %d) → %d\n", base, value);
    base = 16;
    overfscanf(f, "%Cv", &value, base);
    printf("ff  (base %d) → %d\n", base, value);
    base = 8;
    overfscanf(f, "%Cv", &value, base);
    printf("100 (base %d) → %d\n", base, value);

    fclose(f);
    printf("\n");

    printf("[Тест %%CV — чтение числа в системе счисления (прописные буквы)]\n");

    FILE *f2 = fopen("input_CV.txt", "w+");
    fprintf(f2, "1A FF ABC 100");
    rewind(f2);

    base = 16; 
    overfscanf(f2, "%CV", &value, base); 
    printf("1A  (base %d) → %d\n", base, value);
    base = 16; 
    overfscanf(f2, "%CV", &value, base); 
    printf("FF  (base %d) → %d\n", base, value);
    base = 16; 
    overfscanf(f2, "%CV", &value, base); 
    printf("ABC (base %d) → %d\n", base, value);
    base = 8;  
    overfscanf(f2, "%CV", &value, base); 
    printf("100 (base %d) → %d\n", base, value);

    fclose(f2);
    printf("\n");
}

void printTestsForSscanf() {
    printf("Тесты oversscanf\n\n");
    test_Ro_sscanf();
    test_Zr_sscanf();
    test_Cv_CV_sscanf();
    printf("Конец тестов oversscanf\n\n");
}


void printTestsForFscanf() {
    printf("Тесты overfscanf\n\n");
    test_Ro_fscanf();
    test_Zr_fscanf();
    test_Cv_CV_fscanf();
    printf("Конец тестов overfscanf\n\n");
}

void demonstrate() {
    printTestsForSscanf();
    printTestsForFscanf();
}