#ifndef LIVER_H
#define LIVER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"
#include "statusManager.h"

#define MAX_STR_LEN 200

typedef struct {
    int day, month, year;
} BirthDate;

typedef struct {
    size_t id;
    char last_name[MAX_STR_LEN];
    char first_name[MAX_STR_LEN];
    char second_name[MAX_STR_LEN];
    BirthDate birthDate;
    char gender;
    double income;
} Liver;

int days_in_month(int m, int y);

int is_valid_birthdate(BirthDate d);

bool is_latin(char *str);

bool is_correct_first_or_last_name(char *str);

DEFINE_LINKED_LIST(Liver);

#endif