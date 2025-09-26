#include <../include/parseInput.h>
#include "../include/statusManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


Status convertFromStringToDouble(char * st, double * value) {
    if (strlen(st) > 15) {
        return NUMBER_OUT_OF_BOUNDS;
    }
    char *endptr;
    *value = strtod(st, &endptr);
    if (endptr == st) {
        return CANT_CONVERT_TO_NUMBER;
    }

    if (*endptr != '\0') {
        return NOT_A_NUMBER;
    }

    return OK;
}

Status convertFromStringToLong(char * st, long * value) {
    if (strlen(st) > 10) {
        return NUMBER_OUT_OF_BOUNDS;
    }

    char *endptr;
    *value = strtol(st, &endptr, 10);
    if (endptr == st) {
        return CANT_CONVERT_TO_NUMBER;
    }

    if (*endptr != '\0') {
        return NOT_A_NUMBER;
    }

    return OK;
}

Status extractDoublesFromStrings(int argc, char * argv[], double inputVals[], int reqNumOfArgs) {
    int argsOffset = 2;
    if (argc - argsOffset != reqNumOfArgs) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }

    Status status;
    for (int i = 0; i < reqNumOfArgs; i++) {
        status = convertFromStringToDouble(argv[i + argsOffset], &inputVals[i]);
        if (status != OK) {
            return status;
        }
    }
    return OK;
}

Status extractLongsFromStrings(int argc, char * argv[], long inputVals[], int reqNumOfArgs) {
    int argsOffset = 2;
    if (argc - argsOffset != reqNumOfArgs) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }

    Status status;
    for (int i = 0; i < reqNumOfArgs; i++) {
        status = convertFromStringToLong(argv[i + argsOffset], &inputVals[i]);
        if (status != OK) {
            return status;
        }
    }
    return OK;
}