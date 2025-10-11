#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "../include/core.h"

void printTestsForSprintf()
{

    printf("tests for oversprintf:\n");

    char arr[256];

    oversprintf(arr, "Zr: %Zr lld: %lld Ro: %Ro", 5, 5, 5);
    printf("5: %s\n", arr);

    printf("%%Ro:\n");
    int input = 1;
    oversprintf(arr, "%Ro", input);
    printf("res %d: %s\n", input, arr);
    input = 2;
    oversprintf(arr, "%Ro", input);
    printf("res %d: %s\n", input, arr);
    input = 4;
    oversprintf(arr, "%Ro", input);
    printf("res %d: %s\n", input, arr);
    input = 3999;
    oversprintf(arr, "%Ro", input);
    printf("res %d: %s\n", input, arr);
    input = 3888;
    oversprintf(arr, "%Ro", input);
    printf("res %d: %s\n", input, arr);
    printf("-------\n");

    printf("%%Zr:\n");
    unsigned int uinput = 128;
    oversprintf(arr, "%Zr", uinput);
    printf("res %d: %s\n", uinput, arr);
    uinput = 1;
    oversprintf(arr, "%Zr", uinput);
    printf("res %d: %s\n", uinput, arr);
    uinput = 0;
    oversprintf(arr, "%Zr", uinput);
    printf("res %d: %s\n", uinput, arr);
    uinput = 34;
    oversprintf(arr, "%Zr", uinput);
    printf("res %d: %s\n", uinput, arr);
    printf("-------\n");

    printf("%%Cv:\n");
    input = 1;
    int base = 2;
    oversprintf(arr, "%Cv", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 2;
    base = 2;
    oversprintf(arr, "%Cv", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 25;
    base = 37;
    oversprintf(arr, "%Cv", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 25;
    base = 36;
    oversprintf(arr, "%Cv", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 255;
    base = 16;
    oversprintf(arr, "%Cv", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    printf("-------\n");

    printf("%%CV:\n");
    input = 1;
    base = 2;
    oversprintf(arr, "%CV", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 2;
    base = 2;
    oversprintf(arr, "%CV", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 25;
    base = 37;
    oversprintf(arr, "%CV", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 25;
    base = 36;
    oversprintf(arr, "%CV", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    input = 255;
    base = 16;
    oversprintf(arr, "%CV", input, base);
    printf("res %d, base %d: %s\n", input, base, arr);
    printf("-------\n");

    printf("%%to:\n");
    char * inputStr = NULL;
    inputStr = "abc";
    base = 15;
    oversprintf(arr, "%to", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "56";
    base = 37;
    oversprintf(arr, "%to", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "zzz";
    base = 36;
    oversprintf(arr, "%to", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "abc";
    base = 2;
    oversprintf(arr, "%to", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "ff";
    base = 16;
    oversprintf(arr, "%to", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    printf("-------\n");


    printf("%%TO:\n");
    inputStr = "ABC";
    base = 15;
    oversprintf(arr, "%TO", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "56";
    base = 37;
    oversprintf(arr, "%TO", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "ZZZ";
    base = 36;
    oversprintf(arr, "%TO", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "ABC";
    base = 2;
    oversprintf(arr, "%TO", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    inputStr = "FF";
    base = 16;
    oversprintf(arr, "%TO", inputStr, base);
    printf("res %s, base: %d: %s\n", inputStr, base, arr);

    printf("-------\n");

    printf("%%mi:\n");
    input = 256;
    oversprintf(arr, "%mi", input);
    printf("res %d: %s\n", input, arr);

    input = 259;
    oversprintf(arr, "%mi", input);
    printf("res %d: %s\n", input, arr);

    input = -1;
    oversprintf(arr, "%mi", input);
    printf("res %d: %s\n", input, arr);
    
    printf("-------\n");

    printf("%%mu:\n");
    uinput = 256;
    oversprintf(arr, "%mi", uinput);
    printf("res %u: %s\n", uinput, arr);

    uinput = 259;
    oversprintf(arr, "%mi", uinput);
    printf("res %u: %s\n", uinput, arr);

    uinput = 1;
    oversprintf(arr, "%mi", uinput);
    printf("res %u: %s\n", uinput, arr);
    
    printf("-------\n");

    printf("%%md:\n");
    double dinput = 1.5423;
    oversprintf(arr, "%md", dinput);
    printf("res %lf: %s\n", dinput, arr);

    dinput = -45634.3;
    oversprintf(arr, "%md", dinput);
    printf("res %lf: %s\n", dinput, arr);

    dinput = 1;
    oversprintf(arr, "%md", dinput);
    printf("res %lf: %s\n", dinput, arr);
    
    printf("-------\n");

    printf("%%mf:\n");
    float finput = 1.5423;
    oversprintf(arr, "%md", finput);
    printf("res %f: %s\n", finput, arr);

    finput = -45634.3;
    oversprintf(arr, "%md", finput);
    printf("res %f: %s\n", finput, arr);

    finput = 1;
    oversprintf(arr, "%md", finput);
    printf("res %f: %s\n", finput, arr);
    
    printf("-------\n");
}

void printTestsForFprintf()
{
    FILE * fout = fopen("output.txt", "w");
    printf("\n\ntests for overfprintf:\n");

    overfprintf(fout, "5: Zr: %Zr lld: %lld Ro: %Ro\n", 5, 5, 5);

    printf("%%Ro:\n");
    int input = 1;
    overfprintf(stdout, "res %d: %Ro\n", input, input);
    input = 2;
    overfprintf(stdout, "res %d: %Ro\n", input, input);
    input = 4;
    overfprintf(stdout, "res %d: %Ro\n", input, input);
    input = 3999;
    overfprintf(stdout, "res %d: %Ro\n", input, input);
    input = 3888;
    overfprintf(stdout, "res %d: %Ro\n", input, input);
    printf("-------\n");

    printf("%%Zr:\n");
    unsigned int uinput = 128;
    overfprintf(stdout, "res %d: %Zr\n", uinput, uinput);
    uinput = 1;
    overfprintf(stdout, "res %d: %Zr\n", uinput, uinput);
    uinput = 0;
    overfprintf(stdout, "res %d: %Zr\n", uinput, uinput);
    uinput = 34;
    overfprintf(stdout, "res %d: %Zr\n", uinput, uinput);
    printf("-------\n");

    printf("%%Cv:\n");
    input = 1;
    int base = 2;
    overfprintf(stdout, "res %d, base %d: %Cv\n", input, base, input, base);
    input = 2;
    base = 2;
    overfprintf(stdout, "res %d, base %d: %Cv\n", input, base, input, base);
    input = 25;
    base = 37;
    overfprintf(stdout, "res %d, base %d: %Cv\n", input, base, input, base);
    input = 25;
    base = 36;
    overfprintf(stdout, "res %d, base %d: %Cv\n", input, base, input, base);
    input = 255;
    base = 16;
    overfprintf(stdout, "res %d, base %d: %Cv\n", input, base, input, base);
    printf("-------\n");

    printf("%%CV:\n");
    input = 1;
    base = 2;
    overfprintf(stdout, "res %d, base %d: %CV\n", input, base, input, base);
    input = 2;
    base = 2;
    overfprintf(stdout, "res %d, base %d: %CV\n", input, base, input, base);
    input = 25;
    base = 37;
    overfprintf(stdout, "res %d, base %d: %CV\n", input, base, input, base);
    input = 25;
    base = 36;
    overfprintf(stdout, "res %d, base %d: %CV\n", input, base, input, base);
    input = 255;
    base = 16;
    overfprintf(stdout, "res %d, base %d: %CV\n", input, base, input, base);
    printf("-------\n");

    printf("%%to:\n");
    char * inputStr = NULL;
    inputStr = "abc";
    base = 15;
    overfprintf(stdout, "res %s, base: %d: %to\n", inputStr, base, inputStr, base);

    inputStr = "56";
    base = 37;
    overfprintf(stdout, "res %s, base: %d: %to\n", inputStr, base, inputStr, base);

    inputStr = "zzz";
    base = 36;
    overfprintf(stdout, "res %s, base: %d: %to\n", inputStr, base, inputStr, base);

    inputStr = "abc";
    base = 2;
    overfprintf(stdout, "res %s, base: %d: %to\n", inputStr, base, inputStr, base);

    inputStr = "ff";
    base = 16;
    overfprintf(stdout, "res %s, base: %d: %to\n", inputStr, base, inputStr, base);

    printf("-------\n");


    printf("%%TO:\n");
    inputStr = "ABC";
    base = 15;
    overfprintf(stdout, "res %s, base: %d: %TO\n", inputStr, base, inputStr, base);

    inputStr = "56";
    base = 37;
    overfprintf(stdout, "res %s, base: %d: %TO\n", inputStr, base, inputStr, base);

    inputStr = "ZZZ";
    base = 36;
    overfprintf(stdout, "res %s, base: %d: %TO\n", inputStr, base, inputStr, base);

    inputStr = "ABC";
    base = 2;
    overfprintf(stdout, "res %s, base: %d: %TO\n", inputStr, base, inputStr, base);

    inputStr = "FF";
    base = 16;
    overfprintf(stdout, "res %s, base: %d: %TO\n", inputStr, base, inputStr, base);

    printf("-------\n");

    printf("%%mi:\n");
    input = 256;
    overfprintf(stdout, "res %d: %mi\n", input, input);

    input = 259;
    overfprintf(stdout, "res %d: %mi\n", input, input);

    input = -1;
    overfprintf(stdout, "res %d: %mi\n", input, input);
    
    printf("-------\n");

    printf("%%mu:\n");
    uinput = 256;
    overfprintf(stdout, "res %u: %mi\n", uinput, uinput);

    uinput = 259;
    overfprintf(stdout, "res %u: %mi\n", uinput, uinput);

    uinput = 1;
    overfprintf(stdout, "res %u: %mi\n", uinput, uinput);
    
    printf("-------\n");

    printf("%%md:\n");
    double dinput = 1.5423;
    overfprintf(stdout, "res %lf: %md\n", dinput, dinput);

    dinput = -45634.3;
    overfprintf(stdout, "res %lf: %md\n", dinput, dinput);

    dinput = 1;
    overfprintf(stdout, "res %lf: %md\n", dinput, dinput);
    
    printf("-------\n");

    printf("%%mf:\n");
    float finput = 1.5423;
    overfprintf(stdout, "res %f: %md\n", finput, finput);

    finput = -45634.3;
    overfprintf(stdout, "res %f: %md\n", finput, finput);

    finput = 1;
    overfprintf(stdout, "res %f: %md\n", finput, finput);
    
    printf("-------\n");
}

int main()
{
    printTestsForSprintf();
    printTestsForFprintf();
    return 0;
}