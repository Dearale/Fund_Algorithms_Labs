#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/core.h"
#include "../include/parseInput.h"
#include "../include/statusManager.h"

void printUsage() {
    printf("Использование: <имя программы> <флаг> <путь к входному файлу> <путь к выходному файлу, если указан символ n>.\n");
    printf("Пример: \"./task5 -nd input.txt output.txt\"\n");
}


int main(int argc, char * argv[]) {
    char * inputFile, * outputFile;
    char * flag = argv[1];

    Status status = validateInputAndGetFiles(argc, argv, &inputFile, &outputFile);
    if (status != OK) {
        printStatus(status);
        printUsage();
        return 1;
    }
    FILE *fin, *fout;

    fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printStatus(CANT_OPEN_INPUT_FILE);
        return 1;
    }

    fout = fopen(outputFile, "w");
    if (fout == NULL) {
        fclose(fin);
        if (flag[1] != 'n') {
            free(outputFile);
        }
        printStatus(CANT_CREATE_OUTPUT_FILE);
        return 1;
    }

    int flagIndex = 1;
    if (flag[1] == 'n') {
        flagIndex = 2;
    }

    switch(flag[flagIndex]) {
        case 'd':
            processDFlag(fin, fout);
            break;
        case 'i':
            processIFlag(fin, fout);
            break;
        case 's':
            processSFlag(fin, fout);
            break;
        case 'a':
            processAFlag(fin, fout);
            break;
        default:
            printf("Неизвестный флаг: %s\n", flag);
            printUsage();
            fclose(fin);
            fclose(fout);
            if (flag[1] != 'n') {
                free(outputFile);
            }
            return 1;
    }
    
    fclose(fin);
    fclose(fout);
    
    if (flag[1] != 'n') {
        free(outputFile);
    }

    return 0;
}