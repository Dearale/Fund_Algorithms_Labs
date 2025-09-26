#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/core.h"
#include "../include/parseInput.h"
#include "../include/statusManager.h"

void printUsage() {
    printf("Использование: <имя программы> <путь к входному файлу> <путь к выходному файлу>.\n");
    printf("Пример: \"./task5 input.txt output.txt\"\n");
}


int main(int argc, char * argv[]) {
    if (argc != 3) {
        printStatus(WRONG_NUMBER_OF_ARGUMENTS);
        printUsage();
        return 1;
    }

    char *inputFile = argv[1];
    char *outputFile = argv[2];
    FILE *fin, *fout;

    fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printStatus(CANT_OPEN_INPUT_FILE);
        return 1;
    }

    fout = fopen(outputFile, "w");
    if (fout == NULL) {
        fclose(fin);
        printStatus(CANT_CREATE_OUTPUT_FILE);
        return 1;
    }

    processFile(fin, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}