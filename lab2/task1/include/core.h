#ifndef CORE_H
#define CORE_H
#include "statusManager.h"
#include <stdbool.h>
#include <stdarg.h>

Status haveFiniteRepresentations(bool ** res, int base, int count, ...);

#endif