#ifndef CORE_H
#define CORE_H
#include "statusManager.h"
#include <stdbool.h>
#include <stdio.h>


void processDFlag(FILE * fin, FILE * fout);

void processIFlag(FILE * fin, FILE * fout);

void processSFlag(FILE * fin, FILE * fout);

void processAFlag(FILE * fin, FILE * fout);

#endif