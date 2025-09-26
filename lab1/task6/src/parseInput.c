#include <../include/parseInput.h>
#include "../include/statusManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


Status convertFromStringToDouble(char * st, double * value) {
    if (strlen(st) > 11) {
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

    if (*value < 1e-9) {
        return NUMBER_OUT_OF_BOUNDS;
    }

    return OK;
}

Status extractEpsilonFromString(int argc, char * argv[], double * inputVal) {
    if (argc != 2) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }

    Status status = convertFromStringToDouble(argv[1], inputVal);
    if (status == OK && *inputVal <= 0) {
        return INCORRECT_EPSILON;
    }
    return status;
}