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

#define STR_2(x) #x
#define STR(x) STR_2(x)
#define BUFFER_SIZE 1024

int overfscanf(FILE * stream, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const char * fmtp = format;
    int assigned = 0;
    while (*fmtp != '\0') 
    {
        if (*fmtp == '%') 
        {
            fmtp++;
            char buffer[BUFFER_SIZE + 1];
            Specifier spec = getSpecifierType(fmtp);
            fscanf(stream, "%"STR(BUFFER_SIZE)"s", buffer);
            if (spec == OTHER_SPECIFIER) {
                int written = handleStandardSpecifier(&fmtp, args, buffer);
                if (written == -1) {
                    break;
                }
                if (written > 0) {
                    assigned++;
                }
            } else {
                fmtp += getSpecifierLength(spec);
                handleSpecifier(spec, args, buffer);
                assigned += getNumOfReadArguments(spec);
            }
        }  else if (isspace((unsigned char)*fmtp)) {
            while (isspace((unsigned char)*fmtp)) {
                fmtp++;
            }
            int c;
            while ((c = fgetc(stream)) != EOF && isspace((unsigned char)c));
        } else {
            int c;
            if ((c = fgetc(stream)) != EOF && c == *fmtp) {
                fmtp++;
            } else {
                break;
            }
        }
    }

    va_end(args);

    return assigned;
}

int oversscanf(char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char * strp = str;
    const char * fmtp = format;
    int assigned = 0;
    while (*fmtp != '\0') 
    {
        if (*fmtp == '%') 
        {
            fmtp++;
            Specifier spec = getSpecifierType(fmtp);
            if (spec == OTHER_SPECIFIER) {
                
                int written = handleStandardSpecifier(&fmtp, args, strp);
                if (written == -1) {
                    break;
                }
                if (written > 0) {
                    assigned++;
                }

                strp += written;
            } else {
                fmtp += getSpecifierLength(spec);

                int written = handleSpecifier(spec, args, strp);

                strp += written;
                assigned += getNumOfReadArguments(spec);
            }
        } else if (isspace((unsigned char)*fmtp)) {
            while (isspace((unsigned char)*fmtp)) {
                fmtp++;
            }
            while (*strp && isspace((unsigned char)*strp)) {
                strp++;
            }
        } else {
            if (*strp && *strp == *fmtp) {
                strp++;
                fmtp++;
            } else {
                break;
            }
        }

        if (*strp == '\0') {
            break;
        }
    }

    va_end(args);

    return assigned;
}