#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H
#include "statusManager.h"


Status convertFromStringToDouble(char * st, double * value);

Status convertFromStringToLong(char * st, long * value);

Status extractDoublesFromStrings(int argc, char * argv[], double inputVals[], int reqNumOfArgs);

Status extractLongsFromStrings(int argc, char * argv[], long inputVals[], int reqNumOfArgs);

#endif