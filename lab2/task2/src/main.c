#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "../include/core.h"

void printTests()
{
    char a[] = "abcdef";
    char b[] = "abcef";
    
    char * pos = memchr(a, 'd', 5);
    printf("memchr(\"%s\", 'd', 5): %ld\n", a, pos - a);

    printf("memcmp(\"%s\", \"%s\", 6): %d\n", a, b, memcmp(a, b, 6));
    printf("memcmp(\"%s\", \"%s\", 3): %d\n", a, b, memcmp(a, b, 3));
    
    char dest[10];

    memcpy(dest, a, 5);
    printf("memcpy(dest, \"%s\", 5): %s\n", a, dest);

    memset(dest, 'a', 9);
    dest[9] = '\0';

    printf("memset(dest, 'a', 9): %s\n", dest);

    dest[4] = '\0';
    char destSave[10];
    memcpy(destSave, dest, 10);
    strncat(dest, b, 8);

    printf("strncat(\"%s\", \"%s\", 8): %s\n", destSave, b, dest);

    char *res = strchr(a, 'c');

    printf("strchr(\"%s\", c): %s\n", a, res);

    int strncmpRes = strncmp(a, b, 7);
    printf("strncmp(\"%s\", \"%s\", 10): %d\n", a, b, strncmpRes);
    
    strncpy(dest, b, 6);

    printf("strncpy(dest, \"%s\", 4): %s\n", b, dest);

    char c[] = "defg";

    printf("strcspn(\"%s\", \"%s\"): %ld\n", a, c, strcspn(a, c));

    printf("strerror(5): %s\n", strerror(5));
    printf("strerror(15): %s\n", strerror(15));

    printf("strlen(\"%s\"): %ld\n", a, strlen(a));

    char d[] = "dedg";

    res = strrchr(d, 'd');
    printf("strrchr(\"%s\", 'd'): %s\n", d, res);
    
    char e[] = "cde";
    char *p = strstr(a, e);
    printf("strstr(\"%s\", \"%s\"): %s\n", a, e, p);

    char text[] = "1;2.234,";
    const char *delim = ";.,";
    printf("strtok(\"%s\", \"%s\"):\n", text, delim);

    char * tok = strtok(text, delim);
    while (tok != NULL)
    {
        printf("token: %s\n", tok);
        tok = strtok(NULL, delim);
    }
}

int main()
{
    printTests();
    return 0;
}