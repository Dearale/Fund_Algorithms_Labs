#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../include/statusManager.h"
#include "../include/utils.h"

typedef struct {
    int endIndex;
    int spaceCount;
} Word;


void addSpacesToWords(Word words[], int wordCount) {
    int spacesToAdd = SPLIT_COUNT - words[wordCount - 1].endIndex;

    int wordCountToAddSpace = wordCount - 1;
    int addToAll = spacesToAdd / wordCountToAddSpace;
    int leftover = spacesToAdd % wordCountToAddSpace;
    for (int i = 0; i < wordCountToAddSpace; i++)
    {
        words[i].spaceCount += addToAll;
    }

    for (int i = 0; i < leftover; i++)
    {
        words[i].spaceCount++;
    }
}

void fillTmpBufferWithResLine(char tmp[SPLIT_COUNT + 2], char *buffer, Word *words, int wordCount) {
    tmp[SPLIT_COUNT + 1] = '\0';
    char *p = tmp;
    int prevEnd = 0;
    for (int i = 0; i < wordCount; i++)
    {
        buffer[words[i].endIndex] = '\0';
        strcpy(p, buffer + prevEnd);
        p += words[i].endIndex - prevEnd;
        memset(p, ' ', words[i].spaceCount);
        p += words[i].spaceCount;
        prevEnd = words[i].endIndex;
        buffer[words[i].endIndex] = ' ';
    }
    p[0] = '\n';
    p[1] = '\0';
}

void setBufferAndCharCountForNextLine(char tmp[SPLIT_COUNT + 2], char *buffer, Word *words, int wordCount, int *count, int c) {
    int lastEnd = words[wordCount - 1].endIndex;
    buffer[SPLIT_COUNT] = c;
    buffer[SPLIT_COUNT + 1] = '\0';
    strcpy(tmp, buffer);
    while (*(tmp + lastEnd) == ' ') {
        lastEnd++;
    }
    strcpy(buffer, tmp + lastEnd);
    
    *count = SPLIT_COUNT + 1 - lastEnd;
}

Status handleFiles(FILE * fin, FILE * fout) {
    int prevc = '\n';
    int c;
    char buffer[SPLIT_COUNT + 2];
    buffer[SPLIT_COUNT + 1] = '\0';
    int count = 0;
    Word words[SPLIT_COUNT];
    words[0].endIndex = -1;
    int wordCount = 0;
    while ((c = fgetc(fin)) != EOF) {
        if ((c == '\n') || (count == SPLIT_COUNT && isspace((unsigned char)c) && !isspace((unsigned char)prevc))) {
                if (count > 0) {
                    buffer[count] = '\n';
                    buffer[count + 1] = '\0';
                    fputs(buffer, fout);
                }
                count = 0;
                buffer[0] = '\0';
                wordCount = 0;
                c = 0;
        } else if (count == SPLIT_COUNT) {
            if (wordCount == 0) {
                return LINE_OUT_OF_BOUNDS;
            }
            if (wordCount > 1) {
                addSpacesToWords(words, wordCount);
            }

            char tmp[SPLIT_COUNT + 2];
            fillTmpBufferWithResLine(tmp, buffer, words, wordCount);
            fputs(tmp, fout);
            setBufferAndCharCountForNextLine(tmp, buffer, words, wordCount, &count, c);

            c = 0;
            wordCount = 0;
        } else if (!(count == 0 && isspace((unsigned char)c))) {
            if (!isspace((unsigned char)prevc) && isspace((unsigned char)c)) {
                words[wordCount].endIndex = count;
                words[wordCount].spaceCount = 0;
                wordCount++;
            }
            buffer[count] = c;
            count++;
        }
        prevc = c;
    }
    buffer[count] = '\0';
    fputs(buffer, fout);

    return OK;
}