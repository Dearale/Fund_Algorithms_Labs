#include <stdbool.h>
#include <ctype.h>
#include "../include/liver.h"

int days_in_month(int m, int y) {
    static const int d[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int days = (m >= 1 && m <= 12) ? d[m - 1] : 0;
    int leap = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
    if (m == 2 && leap) days = 29;
    return days;
}

int is_valid_birthdate(BirthDate d) {
    if (d.year < 1900 || d.year > 2100) return 0;
    if (d.month < 1 || d.month > 12) return 0;
    int dim = days_in_month(d.month, d.year);
    if (d.day < 1 || d.day > dim) return 0;
    return 1;
}


bool is_latin(char *str) {
    for (char *c = str; *c; c++)
    {
        if (!isalpha(*c)) {
            return false;
        }
    }
    return true;
}

bool is_correct_first_or_last_name(char *str) {
    return str[0] != '\0' && is_latin(str);
}