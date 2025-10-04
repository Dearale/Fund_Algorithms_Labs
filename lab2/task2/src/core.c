#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include "../include/error_messages.h"
#include <stdlib.h>


void *memchr(const void *str, int c, size_t n) 
{
    const unsigned char *st = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;
    for (size_t i = 0; i < n; i++)
    {
        if (st[i] == uc) 
        {
            return (void *)(st + i);
        }
    }
    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n) 
{
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; i++)
    {
        if (s1[i] != s2[i]) 
        {
            return s1[i] - s2[i];
        }
    }
    return 0;    
}

void *memcpy(void *dest, const void *src, size_t n) 
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++)
    {
        d[i] = s[i];
    }

    return dest;
}

void *memset(void *str, int c, size_t n) 
{
    unsigned char * s = (unsigned char *)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        s[i] = uc;
    }

    return str;
    
}

char *strncat(char *dest, const char *src, size_t n) 
{
    char *d = dest;

    while (*d != '\0')
    {
        d++;
    }
    for (size_t i = 0; i < n && src[i] != '\0'; i++)
    {
        *d = src[i];
        d++;   
    }
    *d = '\0';

    return dest;
}

char *strchr(const char *str, int c)
{
    unsigned char uc = (unsigned char)c;
    while (*str != '\0')
    {
        if ((unsigned char)*str == uc) {
            return (char *)str;
        }
        str++;
    }

    if (uc == '\0') 
    {
        return (char *)str;
    }
    
    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n) 
{
    for (size_t i = 0; i < n; i++)
    {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];
        if (c1 != c2) 
        {
            return c1 - c2;
        }

        if (c1 == '\0')
        {
            return 0;
        }
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) 
{
    size_t i = 0;
    for (; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    
    return dest;
}

size_t strcspn(const char *str1, const char *str2)
{
    size_t res = 0;
    for (; str1[res] != '\0'; res++)
    {
        const char *s2 = str2;
        for(; *s2 != '\0'; s2++)
        {
            if (str1[res] == *s2) {
                return res;
            }
        }
    }
    return res;
}

size_t strcspn2(const char *str1, const char *str2)
{
    bool contains[UCHAR_MAX + 1] = { false };

    const unsigned char *p2 = (const unsigned char *)str2;
    for (; *p2 != '\0'; p2++) {
        contains[*p2] = true;
    }

    size_t res = 0;
    for (; str1[res] != '\0'; res++) {
        unsigned char c = (unsigned char)str1[res];
        if (contains[c]) {
            return res;
        }
    }

    return res;
}

char *strerror(int errnum)
{
    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "Unknown error";
    }

    return (char *)(error_messages[errnum]);
}

size_t strlen(const char *str)
{
    size_t res = 0;
    for (; str[res] != '\0'; res++);
    return res;
}

char *strpbrk(const char *str1, const char *str2)
{
    bool contains[UCHAR_MAX + 1] = { false };

    const unsigned char *p2 = (const unsigned char *)str2;
    for (; *p2 != '\0'; p2++) {
        contains[*p2] = true;
    }

    for (; *str1 != '\0'; str1++) {
        if (contains[(unsigned char)*str1]) {
            return (char *)str1;
        }
    }

    return NULL;
}

char *strrchr(const char *str, int c)
{
    unsigned char uc = (unsigned char)c;
    const char * end = str;
    while (*end != '\0')
    {
        end++;
    }

    if (uc == '\0') {
        return (char *)end;
    }
    while (str != end) {
        end--;
        if (*end == uc) {
            return (char *)end;
        }
    }
    return NULL;
}

char *strstr(const char *haystack, const char *needle) 
{
    const char * hp = haystack;
    const char * np = needle;
    while (*hp != '\0') 
    {
        if (*hp == *np) 
        {
            hp++;
            np++;
        } else if (*np == '\0')
        {
            return (char *)haystack;
        } else 
        {
            np = needle;
            haystack++;
            hp = haystack;
        }
    }
    if (*np == '\0') {
        return (char *)haystack;
    }

    return NULL;
}

static int isDelim(char c, const char *delim) {
    for (const char *d = delim; *d != '\0'; d++)
    {
        if (c == *d) {
            return true;
        }
    }
    return false;
}

char *strtok(char *str, const char *delim)
{
    static char *saved = NULL;
    if (str != NULL)
    {
        saved = str;
    } else if (!saved)
    {
        return NULL;
    }

    char *start = saved;
    while (*start != '\0' && isDelim(*start, delim))
    {
        start++;
    }

    if (*start == '\0')
    {
        saved = NULL;
        return NULL;
    }

    char *end = start;
    while (*end != '\0' && !isDelim(*end, delim))
    {
        end++;
    }

    if (*end == '\0')
    {
        saved = NULL;
        return start;
    }

    *end = '\0';
    saved = end + 1;
    return start;
}
