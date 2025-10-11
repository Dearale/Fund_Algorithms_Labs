#include "../include/specifiers.h"
#include "../include/functions.h"
#include <stdarg.h>

const char *specifiers = "diuoxXfFeEgGaAcspn%[]";


Specifier getSpecifierType(const char * formatPointer) {
    const char * fmtp = formatPointer;
    if (fmtp[0] == 'R' && fmtp[1] == 'o')
        return RIM_NUMBER; 
    if (fmtp[0] == 'Z' && fmtp[1] == 'r')
        return ZECKENDORF;
    if (fmtp[0] == 'C') {
        if (fmtp[1] == 'v') 
            return CONVERT_TO_BASE_10_LOWER;
        if (fmtp[1] == 'V') 
            return CONVERT_TO_BASE_10_UPPER;
    }
    return OTHER_SPECIFIER;
}

int getSpecifierLength(Specifier spec) {
    switch (spec) {
        case RIM_NUMBER:
        case ZECKENDORF:
        case CONVERT_TO_BASE_10_LOWER:
        case CONVERT_TO_BASE_10_UPPER:
            return 2;
        default:
            return -1;
    }
}

int getNumOfReadArguments(Specifier spec) {
    switch (spec) {
        case RIM_NUMBER:
        case ZECKENDORF:
        case CONVERT_TO_BASE_10_UPPER:
        case CONVERT_TO_BASE_10_LOWER:
            return 1;
        default:
            return 0;
    }
}

int handleRimSpecifier(va_list args, char * input) {
    int *num = va_arg(args, int *);
    return convertFromRim(num, input);
}

int handleZeckendorfSpecifier(va_list args, char * input) {
    unsigned int *num = va_arg(args, unsigned int *);
    return fromZeckendorf(num, input);
}

int handleConvertToBase10Specifiers(Specifier spec, va_list args, char * input) {
    int * num = va_arg(args, int *);
    int base = va_arg(args, int);

    bool isCapital = (spec == CONVERT_TO_BASE_10_UPPER);
    return convertToBase10(input, base, num, isCapital);
}

int handleSpecifier(Specifier spec, va_list args, char * out) {
    switch (spec) {
        case RIM_NUMBER:
            return handleRimSpecifier(args, out);

        case ZECKENDORF:
            return handleZeckendorfSpecifier(args, out);

        case CONVERT_TO_BASE_10_LOWER:
        case CONVERT_TO_BASE_10_UPPER:
            return handleConvertToBase10Specifiers(spec, args, out);
        
        default:
            return 0;

    }

    return 0;
}

int handleStandardSpecifier(const char **format, va_list args, char *strp) {
    #define HANDLE_TYPE(type) \
        type *out = va_arg(args, type *); \
        *out = (type)val; \
        (*format)++; \
    
    const char * fmtp = *format;
    char * endptr = NULL;
    if (fmtp[0] == 'd') {
        long val = strtol(strp, &endptr, 10);
        HANDLE_TYPE(int);
    } else if (fmtp[0] == 'u') {
        unsigned long val = strtoul(strp, &endptr, 10);
        HANDLE_TYPE(unsigned);
    } else if (fmtp[0] == 'x') {
        unsigned long val = strtoul(strp, &endptr, 16);
        HANDLE_TYPE(unsigned);
    } else if (fmtp[0] == 'f') {
        double val = strtod(strp, &endptr);
        HANDLE_TYPE(float);
    } else if (fmtp[0] == 'l') {
        if (fmtp[1] == 'f') {
            double val = strtod(strp, &endptr);
            HANDLE_TYPE(double);
            (*format)++;
        }
    } else if (fmtp[0] == 's') {
        char *start = strp;
        while (*start && isspace((unsigned char)*start)) {
            start++;
        }

        char *out = va_arg(args, char *);
        endptr = start;
        while (*endptr && !isspace((unsigned char)*endptr)) {
            out[endptr - start] = *endptr;
            endptr++;
        }
        out[endptr - start] = '\0';
        (*format)++;
    }

    if (endptr == strp) {
        return -1;
    }

    if (endptr == NULL) {
        return 0;
    }

    return endptr - strp;
}
