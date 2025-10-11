#ifndef SPECIFIERS_H
#define SPECIFIERS_H
#include <stdarg.h>



typedef enum {
    RIM_NUMBER,
    ZECKENDORF,
    CONVERT_TO_BASE_10_LOWER,
    CONVERT_TO_BASE_10_UPPER,
    OTHER_SPECIFIER
} Specifier;

Specifier getSpecifierType(const char * formatPointer);

int getSpecifierLength(Specifier spec);
int getNumOfReadArguments(Specifier spec);

int handleRimSpecifier(va_list args, char * out);

int handleZeckendorfSpecifier(va_list args, char * out);

int handleConvertToBase10Specifiers(Specifier spec, va_list args, char * out);

int handleSpecifier(Specifier spec, va_list args, char * out);

int handleStandardSpecifier(const char **format, va_list args, char * out);


#endif