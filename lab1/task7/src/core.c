#include "../include/core.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>

#define MAX_WORD_LENGTH 63


bool convertToBase10(char word[], int base, long long * number) {
    *number = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int num = word[i] - '0';
        if (word[i] >= 'a') {
            num = word[i] - 'a' + 10;
        }
        if ((LLONG_MAX - num) / base < *number) {
            return false;
        }

        *number = *number * base + num;
    }

    return true;
}

typedef struct {
    bool validNumber;
    int length;
    char word[MAX_WORD_LENGTH + 1];
    bool containsLeadingZeros;
    bool containsLeadingPlus;
    int minBase;
    bool isPositive;
    FILE *fout;
} WordData;

void processWord(WordData *data) {
    if (!data->validNumber)
        return;
    
    long long numInBase10 = 0;
    data->word[data->length] = '\0';
    if (data->length == 0 && data->containsLeadingZeros) {
        data->word[0] = '0';
        data->word[1] = '\0';
        data->length = 1;
    }
    if (data->length != 0 && convertToBase10(data->word, data->minBase, &numInBase10)) {
        if (!data->isPositive && numInBase10 != 0) {
            fputc('-', data->fout);
        }
        fwrite(data->word, sizeof(char), data->length, data->fout);
        fprintf(data->fout, " %d ", data->minBase);

        if (!data->isPositive && numInBase10 != 0) {
            fputc('-', data->fout);
        }
        fprintf(data->fout, "%lld\n", numInBase10);
    }
}

void resetWordData(WordData * data) {
    data->validNumber = true;
    data->length = 0;
    data->containsLeadingZeros = false;
    data->containsLeadingPlus = false;
    data->minBase = 2;
    data->isPositive = true;
}

void processFile(FILE * fin, FILE * fout) {
    WordData data;
    resetWordData(&data);
    data.fout = fout;

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (isspace(ch)) {
            processWord(&data);
            resetWordData(&data);
            continue;
        }

        if (!data.validNumber)
        {
            continue;
        }

        if (data.isPositive && !data.containsLeadingPlus && !data.containsLeadingZeros && data.length == 0) {
            if (ch == '-'){
                data.isPositive = false;
                continue;
            } if (ch == '+') {
                data.containsLeadingPlus = true;
                continue;
            }
        }

        ch = tolower(ch);
        if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z')) {
            if (data.length == 0 && ch == '0') {
                data.containsLeadingZeros = true;
                continue;
            }
            
            if (data.length >= MAX_WORD_LENGTH) {
                data.validNumber = false;
                continue;
            }

            data.word[data.length] = ch;
            data.length++;

            int base = 2;
            if ('0' <= ch && ch <= '9') {
                base = ch - '0' + 1;
            } else {
                base = ch - 'a' + 11;
            }

            if (base > data.minBase) {
                data.minBase = base;
            }

        } else {
            data.validNumber = false;
            data.length = 0;
            continue;
        }
    }
    processWord(&data);
}