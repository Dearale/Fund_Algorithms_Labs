#include "../include/parseInput.h"

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

Status isValidNumber(const char * st) {
    int length = 0;
    for (size_t i = 0; st[i] != '\0'; i++)
    {
        if (!isdigit(st[i])) {
            return UNALLOWED_NUMBER;
        }
        if (length || st[i] != '0')
            length++;
    }
    if (length > 10)
    {
        return NUMBER_OUT_OF_BOUNDS;
        return 0;
    }
    return OK;  
}

Status parseInputAndReturnIsValid(int argc, char * argv[], char * flag, int * x) {
    if (argc != 3)
        return WRONG_NUMBER_OF_ARGUMENTS;

    Status numberIsValidStatus = isValidNumber(argv[1]);
    if (numberIsValidStatus != OK) {
        return numberIsValidStatus;
    }
    
    if ((argv[2][0] != '-' && argv[2][0] != '/') || strlen(argv[2]) != 2)
        return INCORRECT_FLAG_FORMAT;

    char *endptr;
    long long inputValue = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return UNALLOWED_NUMBER;
    }
    if (inputValue > INT_MAX) {
        return NUMBER_OUT_OF_BOUNDS;
    }

    *x = (int) inputValue;
    *flag = argv[2][1];

    return OK;
}
