#include <limits.h>
#include <stdbool.h>
#include "../include/core.h"

int addOne(int src) {
    int carry = 1;
    while (carry) {
        int curCarry = src & carry;
        src ^= carry;
        carry = curCarry << 1;
    }
    return src;
}

int negate(int src) {
    return addOne(~src);
}

int subOne(int src) {
    return negate(addOne(negate(src)));
}

void reverseString(char * res, int len) {
    int i = 0;
    int j = subOne(len);
    while (i < j) {
        char tmp = res[i];
        res[i] = res[j];
        res[j] = tmp;
        i = addOne(i);
        j = subOne(j);
    }
}


void convertTo2Base(int number, int r, char * res) {
    if (number == 0) {
        res[0] = '0';
        res[1] = '\0';
        return;
    }

    if (r < 1 || r > 5) {
        res[0] = '\0';
        return;
    }

    int mask = ~(INT_MAX << r);

    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int index = 0;
    bool isPositive = true;
    if (number < 0) {
        isPositive = false;
        if (number == INT_MIN) {
            res[index] = '0';
            index = addOne(index);
            number >>= r;
        }
        number = negate(number);
    }

    while (number) {
        int leftover = number & mask;
        res[index] = digits[leftover];
        number >>= r;
        index = addOne(index);
    }

    if (!isPositive) {
        res[index] = '-';
        index = addOne(index);
    }
    reverseString(res, index);
    res[index] = '\0';
}
