#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/core.h"

int main() {
    char path[MAX_LENGTH];

    printf("Введите путь к входному файлу:\n");
    scanf("%s", path);

    FILE * fin = fopen(path, "r");
    if (!fin) {
        printf("Ошибка: не удалось открыть файл.");
        return 1;
    }

    printf("Введите путь к выходному файлу:\n");
    scanf("%s", path);

    FILE * fout = fopen(path, "w");
    if (!fout) {
        printf("Ошибка: не удалось открыть файл.");
        return 1;
    }

    printStatus(handleFiles(fin, fout));

    return 0;
}