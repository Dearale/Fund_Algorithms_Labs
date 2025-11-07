#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/liver_ops.h"
#include "../include/liver.h"

#define STR_2(x) #x
#define STR(x) STR_2(x)

int read_resident_with_second_name(char *buffer, size_t *id, char *last_name, char *first_name, 
                                    char *second_name, int *day, 
                                    int *month, int *year, char *gender, double *income) {
    return sscanf(buffer, "%zu %" STR(MAX_STR_LEN) "s %" STR(MAX_STR_LEN) 
            "s %" STR(MAX_STR_LEN) "s %d %d %d %c %lf",
            id, last_name, first_name, second_name, day, month,
            year, gender, income);
}

int read_resident_without_second_name(char *buffer, size_t *id, char *last_name, 
                                    char *first_name, int *day, 
                                    int *month, int *year, char *gender, double *income) {
    return sscanf(buffer, "%zu %" STR(MAX_STR_LEN) "s %" STR(MAX_STR_LEN) "s %d %d %d %c %lf",
            id, last_name, first_name, day, month, year, gender, income);
}

Status read_resident(char *buffer, Liver *l) {
    size_t id;
    char last_name[MAX_STR_LEN];
    char first_name[MAX_STR_LEN];
    char second_name[MAX_STR_LEN];
    char gender;
    int day, month, year;
    double income;
    int c;
    if ((c = read_resident_with_second_name(buffer, &id, last_name, first_name, 
                                        second_name, &day, &month, 
                                        &year, &gender,&income)) != 9){
        if ((c = read_resident_without_second_name(buffer, &id, last_name, first_name, 
            &day, &month, &year, &gender, &income)) != 8) {
                
                return INVALID_INPUT;
        }
        second_name[0] = '\0';
    }

    if (!is_latin(last_name) || !is_latin(first_name) || !is_latin(second_name) 
        || income < 0 || (gender != 'M' && gender != 'W')) {
        return INVALID_INPUT;
    }


    l->id = id;
    l->birthDate.day = day;
    l->birthDate.month = month;
    l->birthDate.year = year;
    l->gender = gender;
    l->income = income;
    strncpy(l->first_name, first_name, MAX_STR_LEN - 1);
    strncpy(l->last_name, last_name, MAX_STR_LEN - 1);
    strncpy(l->second_name, second_name, MAX_STR_LEN - 1);

    return OK;
}

Status read_residents(FILE * fin, LinkedList *residents) {
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, sizeof(buffer), fin)) {
        Liver l;
        if (read_resident(buffer, &l) != OK)
            continue;
        if (contains_id(residents, l.id)) {
            continue;
        }
        insert_sorted_by_age(residents, &l);
    }

    return OK;
}