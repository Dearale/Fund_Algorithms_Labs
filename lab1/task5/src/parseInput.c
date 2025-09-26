#include <../include/parseInput.h>
#include "../include/statusManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


Status validateInputAndGetFiles(int argc, char * argv[], char ** inputFile, char ** outputFile) {
    if (argc < 3 || argc > 4) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }
    char * flag = argv[1];

    size_t stLen = strlen(flag);
    if ((flag[0] != '-' && flag[0] != '/') || stLen < 2 || stLen > 3) {
        return INCORRECT_FLAG_FORMAT;
    }

    *inputFile = argv[2];
    *outputFile = NULL;
    if (flag[1] == 'n') {
        if (argc != 4) {
            return WRONG_NUMBER_OF_ARGUMENTS;
        }

        if (strlen(flag) != 3) {
            return INCORRECT_FLAG_FORMAT;
        }

        *outputFile = argv[3];
    } else {
        if (argc != 3) {
            return WRONG_NUMBER_OF_ARGUMENTS;
        }
        if (strlen(flag) != 2) {
            return INCORRECT_FLAG_FORMAT;
        }

        char *fileName = *inputFile;
        char *lastSlash = strrchr(*inputFile, '/');
        char *lastBackslash = strrchr(*inputFile, '\\');

        if (lastBackslash > lastSlash) {
            lastSlash = lastBackslash;
        }

        if (lastSlash != NULL) {
            fileName = lastSlash + 1;
        }

        *outputFile = (char*)malloc(strlen(*inputFile) + 5);
        if (*outputFile == NULL) {
            return MEMORY_ERROR;
        }
        strncpy(*outputFile, *inputFile, fileName - *inputFile);
        strcat(*outputFile, "out_");
        strcat(*outputFile, fileName);
    }
    return OK;
}
