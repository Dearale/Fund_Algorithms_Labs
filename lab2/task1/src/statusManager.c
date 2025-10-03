#include "../include/statusManager.h"
#include <stdio.h>

void printStatus(Status status) {
    switch (status) {
        case NUMBER_OUT_OF_BOUNDS:
            printf("Все числа должны быть в диапазоне (0;1)\n");
            break;
        case MEMORY_ERROR:
            printf("Ошибка выделения памяти\n");
            break;
        case BASE_OUT_OF_BOUNDS:
            printf("Переданная система счисления должна быть больше или равна 2\n");
            break;
        default:
            break;
    }
}