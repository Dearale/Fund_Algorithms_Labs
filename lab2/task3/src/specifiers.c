#include "../include/specifiers.h"
#include "../include/functions.h"
#include <stdarg.h>

const char *specifiers = "diuoxXfFeEgGaAcspn%";


Specifier getSpecifierType(const char * formatPointer) {
    const char * fmtp = formatPointer;
    if (fmtp[0] == 'R' && fmtp[1] == 'o')
        return RIM_NUMBER; 
    if (fmtp[0] == 'Z' && fmtp[1] == 'r')
        return ZECKENDORF;
    if (fmtp[0] == 'C') {
        if (fmtp[1] == 'v') 
            return CONVERT_FROM_BASE_10_LOWER;
        if (fmtp[1] == 'V') 
            return CONVERT_FROM_BASE_10_UPPER;
        return OTHER_SPECIFIER;
    }
    if (fmtp[0] == 't' && fmtp[1] == 'o') 
        return CONVERT_TO_BASE_10_LOWER;
    if (fmtp[0] == 'T' && fmtp[1] == 'O') 
        return CONVERT_TO_BASE_10_UPPER;
    if (fmtp[0] == 'm') {
        if (fmtp[1] == 'i') 
            return MEMORY_DUMP_INT;
        if (fmtp[1] == 'u') 
            return MEMORY_DUMP_UINT;
        if (fmtp[1] == 'd') 
            return MEMORY_DUMP_DOUBLE;
        if (fmtp[1] == 'f') 
            return MEMORY_DUMP_FLOAT;
    }

    return OTHER_SPECIFIER;
}

int getSpecifierLength(Specifier spec) {
    switch (spec) {
        case RIM_NUMBER:
        case ZECKENDORF:
        case CONVERT_FROM_BASE_10_LOWER:
        case CONVERT_FROM_BASE_10_UPPER:
        case CONVERT_TO_BASE_10_LOWER:
        case CONVERT_TO_BASE_10_UPPER:
        case MEMORY_DUMP_INT:
        case MEMORY_DUMP_UINT:
        case MEMORY_DUMP_DOUBLE:
        case MEMORY_DUMP_FLOAT:
            return 2;
        default:
            return -1;
    }
}

int handleRimSpecifier(va_list args, char * out) {
    int num = va_arg(args, int);
    char rimOutput[MAX_RIM_NUM_LEN + 1];
    convertToRim(num, rimOutput);
    return sprintf(out, "%s", rimOutput);
}

int handleZeckendorfSpecifier(va_list args, char * out) {
    unsigned int num = va_arg(args, unsigned int);
    char output[MAX_ZECKENDORF_LEN];
    toZeckendorf(num, output);
    return sprintf(out, "%s", output);
}

int handleConvertFromBase10Specifiers(Specifier spec, va_list args, char * out) {
    int num = va_arg(args, int);
    int base = va_arg(args, int);
    char output[MAX_NUM_LEN + 1];

    bool isCapital = (spec == CONVERT_FROM_BASE_10_UPPER);
    convertFromBase10To(base, num, output, isCapital);
    return sprintf(out, "%s", output);
}

int handleConvertToBase10Specifiers(Specifier spec, va_list args, char * out) {
    char * str = va_arg(args, char *);
    int base = va_arg(args, int);

    int result = 0;
    bool isCapital = (spec == CONVERT_TO_BASE_10_UPPER);
    convertToBase10(str, base, &result, isCapital);
    return sprintf(out, "%d", result);
}


int handleMemoryDumpSpecifiers(Specifier spec, va_list args, char * out) {
    #define DUMP_TYPE(type, spec) \
    case spec: { \
        type val = va_arg(args, type); \
        return dumpBytes(&val, out, sizeof(type)); \
    }
    
    switch (spec) {
        DUMP_TYPE(int, MEMORY_DUMP_INT);
        DUMP_TYPE(unsigned int, MEMORY_DUMP_UINT);
        DUMP_TYPE(int, MEMORY_DUMP_DOUBLE);
        case MEMORY_DUMP_FLOAT: {
            float val = (float)va_arg(args, double);
            return dumpBytes(&val, out, sizeof(float));
        }
        default:
            return 0;
    }
}

int handleSpecifier(Specifier spec, va_list args, char * out) {
    switch (spec) {
        case RIM_NUMBER:
            return handleRimSpecifier(args, out);

        case ZECKENDORF:
            return handleZeckendorfSpecifier(args, out);

        case CONVERT_FROM_BASE_10_LOWER:
        case CONVERT_FROM_BASE_10_UPPER:
            return handleConvertFromBase10Specifiers(spec, args, out);

        case CONVERT_TO_BASE_10_LOWER:
        case CONVERT_TO_BASE_10_UPPER:
            return handleConvertToBase10Specifiers(spec, args, out);
        
        case MEMORY_DUMP_INT:
        case MEMORY_DUMP_UINT:
        case MEMORY_DUMP_DOUBLE:
        case MEMORY_DUMP_FLOAT:
            return handleMemoryDumpSpecifiers(spec, args, out);
        default:
            return 0;

    }

    return 0;
}

int handleStandardSpecifier(const char **format, va_list args, char * out) {
    const int fmtbuflen = 64;
    char fmtbuf[fmtbuflen + 1];
    char *bufp = fmtbuf;
    *bufp++ = '%';
    
    while ((bufp - fmtbuf < fmtbuflen - 1) && **format != '\0' && strchr(specifiers, **format) == NULL)
    {
        *bufp++ = **format;
        (*format)++;
    }

    if (**format != '\0')
    {
        *bufp++ = **format;
        (*format)++;
    }
    *bufp = '\0';

    return vsprintf(out, fmtbuf, args);
}
