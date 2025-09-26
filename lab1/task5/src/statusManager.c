#include "../include/statusManager.h"
#include <stdio.h>

void printStatus(Status status) {
    switch (status) {
        case NOT_A_NUMBER:
            printf("В строке есть посторонние символы\n");
            break;
        case CANT_CONVERT_TO_NUMBER:
            printf("Не удалось преобразовать строку в число\n");
            break;
        case WRONG_NUMBER_OF_ARGUMENTS:
            printf("Неверное количество параметров\n");
            break;
        case NO_ZEROS_FOR_MULTIPLES:
            printf("Оба числа должны быть ненулевыми\n");
            break;
        case INCORRECT_FLAG_FORMAT:
            printf("Некорректный формат флага\n");
            break;
        case INCORRECT_EPSILON:
            printf("Эпсилон должен быть положительным\n");
            break;
        case NUMBER_OUT_OF_BOUNDS:
            printf("Число выходит за пределы допустимых значений\n");
            break;
        case MEMORY_ERROR:
            printf("Ошибка выделения памяти\n");
            break;
        case CANT_OPEN_INPUT_FILE:
            printf("Не удалось открыть файл с входными данными\n");
            break;
        case CANT_CREATE_OUTPUT_FILE:
            printf("Не удалось создать файл с выходными данными\n");
            break;
        default:
            break;
    }
    return;
}