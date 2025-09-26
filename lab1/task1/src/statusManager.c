#include "../include/statusManager.h"
#include <limits.h>
#include <stdio.h>

void printStatus(Status status) {
    switch (status) {
        case WRONG_NUMBER_OF_ARGUMENTS:
            printf("Передано неверное количество аргументов\n");
            break;
        case UNALLOWED_NUMBER:
            printf("Ошибка: это число не является допустимым. Число должно быть в диапазоне от 0 до %d\n", INT_MAX);
            break;
        case INCORRECT_FLAG_FORMAT:
            printf("Некорректный формат флага\n");
            break;
        case NUMBER_OUT_OF_BOUNDS:
            printf("Число должно быть в диапазоне от нуля до %d\n", INT_MAX);
            break;
        case DIVISION_BY_ZERO:
            printf("Деление на 0 невозможно. Требуется число больше 0\n");
            break;
        case OUT_OF_BOUNDS_FOR_DEGREE_TABLE:
            printf("Для вывода таблицы число должен быть в диапазоне от 1 до 10\n");
            break;
        case OUT_OF_BOUNDS_FOR_SUM_UP_TO_X:
            printf("Можно вводить только положительные числа\n");
            break;
        case OUT_OF_BOUNDS_FOR_FACTORIAL:
            printf("Для получения факториала число должно быть в диапазоне от 0 до 20\n");
            break;
        default:
            break;
    }
}