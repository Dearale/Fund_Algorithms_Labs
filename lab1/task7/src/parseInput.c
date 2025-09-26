#include <../include/parseInput.h>
#include "../include/statusManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


Status validateInputAndGetFiles(int argc, char * argv[], char ** inputFile, char ** outputFile) {
    if (argc != 3) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }

    *inputFile = argv[1];
    *outputFile = argv[2];
    return OK;
}
