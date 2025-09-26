#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H
#include "statusManager.h"


Status convertFromStringToDouble(char * st, double * value);


Status extractEpsilonFromString(int argc, char * argv[], double *inputVal);


#endif