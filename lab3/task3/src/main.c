#include "../include/demonstration.h"
#include "../include/liver_ops.h"
#include "../include/liver_read.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define STR_2(x) #x
#define STR(x) STR_2(x)

void printUsage() {
    printf("Использование: ./main.out <входной файл> <выходной файл>.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printUsage();
        return 1;
    }
    char *inPath = argv[1];
    FILE *fin = fopen(inPath, "r");
    if (!fin) {
        printf("Ошибка: не удалось открыть входной файл.");
        return 1;
    }

    char *outPath = argv[2];
    FILE *fout = fopen(outPath, "w");
    if (!fout) {
        printf("Ошибка: не удалось открыть выходной файл.");
        return 1;
    }
    fclose(fout);

    LinkedList list = create_resident_list();
    Status status = read_residents(fin, &list);
    if (status != OK) {
        printStatus(status);
        return 1;
    }
    fclose(fin);

    demonstrate(&list, outPath);
    return 0;
}