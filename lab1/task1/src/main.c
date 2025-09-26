#include "../include/core.h"
#include "../include/parseInput.h"

#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    char flag;
    int x;

    Status status = parseInputAndReturnIsValid(argc, argv, &flag, &x);
    if (status != OK){
        printStatus(status);
        printUsage();
        return 1;
    }

    switch (flag) {
        case 'h':
            printStatus(printNaturals(x));
            break;
        case 'p':
            printStatus(printIsPrimeOrComposite(x));
            break;
        case 's':
            printStatus(printIn16NumSystem(x));
            break;
        case 'e':
            printStatus(printPowerTable(x));
            break;
        case 'a':
            printStatus(printSumUpToX(x));
            break;
        case 'f':
            printStatus(printFactorial(x));
            break;
        default:
            printf("Неизвестный флаг: %s\n", argv[2]);
            printUsage();
            return 1;
    }
    return 0;
}

//INT_MAX: 2147483647