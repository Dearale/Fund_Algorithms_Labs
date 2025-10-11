#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

int overfprintf(FILE * stream, const char *format, ...);

int oversprintf(char *str, const char *format, ...);

#endif