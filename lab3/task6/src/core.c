#include <limits.h>
#include <stdbool.h>
#include "../include/core.h"

int check_brackets(const char *str) {
    int round_num = 0;
    int square_num = 0;
    int figure_num = 0;
    int angled_num = 0;
    
    const char *p = str;
    while (*p) {
        if (*p == '(') {
            round_num++;
        } else if (*p == '[') {
            square_num++;
        } else if (*p == '{') {
            figure_num++;
        } else if (*p == '<') {
            angled_num++;
        } else if (*p == ')') {
            if (round_num > 0) {
                round_num--;
            } else {
                round_num = false;
            }
        }
        p++;
    }
}