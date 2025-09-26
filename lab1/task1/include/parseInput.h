#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include "statusManager.h"

Status parseInputAndReturnIsValid(int argc, char * argw[], char * flag, int * x);

Status isValidNumber(const char * st);

#endif