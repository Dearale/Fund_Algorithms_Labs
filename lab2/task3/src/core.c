#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../include/specifiers.h"
#include "../include/functions.h"

#define BUFFER_SIZE 1024

int overfprintf(FILE * stream, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const char * fmtp = format;
    int written = 0;
    while (*fmtp != '\0') 
    {
        if (*fmtp == '%') 
        {
            fmtp++;
            char buffer[BUFFER_SIZE + 1];
            Specifier spec = getSpecifierType(fmtp);
            int curWritten = 0;
            if (spec == OTHER_SPECIFIER) {
                curWritten = handleStandardSpecifier(&fmtp, args, buffer);
            } else {
                fmtp += getSpecifierLength(spec);
                curWritten = handleSpecifier(spec, args, buffer);
            }

            buffer[curWritten] = '\0';

            fprintf(stream, "%s", buffer);
            written += curWritten;
        } else
        {
            fputc(*fmtp, stream);
            written++;
            fmtp++;
        }
    }

    va_end(args);

    return written;
}

int oversprintf(char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char * strp = str;
    const char * fmtp = format;
    while (*fmtp != '\0') 
    {
        if (*fmtp == '%') 
        {
            fmtp++;
            Specifier spec = getSpecifierType(fmtp);
            if (spec == OTHER_SPECIFIER) {
                strp += handleStandardSpecifier(&fmtp, args, strp);
            } else {
                fmtp += getSpecifierLength(spec);
                strp += handleSpecifier(spec, args, strp);
            }
        } else
        {
            *strp = *fmtp;
            strp++;
            fmtp++;
        }
    }

    *strp = '\0';
    va_end(args);

    return strp - str;
}