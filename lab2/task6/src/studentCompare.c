#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/studentCompare.h"


int cmpId(const void *a, const void *b) {
    return ((Student *)a)->id - ((Student *)b)->id;
}

int cmpFirstName(const void *a, const void *b) {
    return strcmp(((Student *)a)->firstName, ((Student *)b)->firstName);
}

int cmpLastName(const void *a, const void *b) {
    return strcmp(((Student *)a)->lastName, ((Student *)b)->lastName);
}

int cmpGroup(const void *a, const void *b) {
    return strcmp(((Student *)a)->group, ((Student *)b)->group);
}
