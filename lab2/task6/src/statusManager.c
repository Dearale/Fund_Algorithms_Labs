#include "../include/statusManager.h"
#include <stdio.h>
#include <utils.h>

void printStatus(Status status) {
    switch (status) {
        case LINE_OUT_OF_BOUNDS:
            printf("Ошибка: в файле есть слово длиннее " STR(SPLIT_COUNT) " символов\n");
            break;
        default:
            break;
    }
}