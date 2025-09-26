#include <stdio.h>
#include <stdlib.h>
#include "../include/statusManager.h"
#include "../include/core.h"
#include "../include/parseInput.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printStatus(WRONG_NUMBER_OF_ARGUMENTS);
        return 1;
    }

    if ((argv[1][0] != '-' && argv[1][0] != '/') || strlen(argv[1]) != 2) {
        printStatus(INCORRECT_FLAG_FORMAT);
        return 1;
    }
    char flag = argv[1][1];

    double inputVals[4] = {};
    switch (flag) {
        case 'q': {
            Status status = extractDoublesFromStrings(argc, argv, inputVals, 4);
            if (status != OK) {
                printStatus(status);
                return 1;
            } else {
                printStatus(printEquationSolutions(inputVals));
            }
        }
        break;
        case 'm': {
            long inputValsLong[2] = {};
            Status status = extractLongsFromStrings(argc, argv, inputValsLong, 2);
            if (status != OK) {
                printStatus(status);
                return 1;
            } else {
                printStatus(printIsFirstMultipleOfSecond(inputValsLong[0], inputValsLong[1]));
            }
        }
        break;
        case 't': {
            Status status = extractDoublesFromStrings(argc, argv, inputVals, 4);
            if (status != OK) {
                printStatus(status);
                return 1;
            } else {
                printStatus(printCanBeRightTriangle(inputVals));
            }
        }
        break;
        default:
            printf("Неизвестный флаг");
            return 1;

    }

    return 0;
}