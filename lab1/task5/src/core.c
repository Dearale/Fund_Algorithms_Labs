#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>

void processDFlag(FILE * fin, FILE * fout) {
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, fout);
        }
    }
}

void processIFlag(FILE * fin, FILE * fout) {
    int ch;
    int latinCount = 0;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == '\n') {
            fprintf(fout, "%d\n", latinCount);
            latinCount = 0;
        } else if (isalpha(ch)) {
            latinCount++;
        }
    }
    fprintf(fout, "%d\n", latinCount);
}

void processSFlag(FILE * fin, FILE * fout) {
    setlocale(LC_ALL, "");
    wint_t ch;
    int count = 0;
    while ((ch = fgetwc(fin)) != WEOF) {
        if (ch == L'\n') {
            fprintf(fout, "%d\n", count);
            count = 0;
        } else if (!((ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z')) && !iswspace(ch) && !iswdigit(ch)) {
            count++;
        }
    }
    fprintf(fout, "%d\n", count);
}

void processAFlag(FILE * fin, FILE * fout) {
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (isdigit(ch)) {
            fputc(ch, fout);
        } else {
            fprintf(fout, "%X", ch);
        }
    }
}