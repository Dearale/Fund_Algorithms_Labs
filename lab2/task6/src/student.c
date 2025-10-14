#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "../include/student.h"
#include "../include/statusManager.h"
#include "../include/utils.h"

bool isLatin(char *str) {
    for (char *c = str; *c; c++)
    {
        if (!isalpha(*c)) {
            return false;
        }
    }
    return true;
}

Status readStudents(FILE * fin, Students *students) {
    char buffer[MAX_STRING];
    students->size = 0;
    students->data = NULL;
    while (fgets(buffer, sizeof(buffer), fin)) {
        Student s;
        unsigned int id;
        char firstName[MAX_STRING + 1];
        char lastName[MAX_STRING + 1];
        char group[MAX_STRING + 1];
        unsigned char grades[GRADE_NUM];
        
        if (sscanf(buffer, "%u %" STR(MAX_STRING) "s %" STR(MAX_STRING) 
            "s %" STR(MAX_STRING) "s %c %c %c %c %c",
            &id, firstName, lastName, group, grades, grades + 1, grades + 2,
            grades + 3, grades + 4) != 9) {
                continue;
        }

        if (!isLatin(firstName) || !isLatin(lastName)) {
            continue;
        }

        s.id = id;
        s.firstName = malloc(strlen(firstName) + 1);
        s.lastName = malloc(strlen(lastName) + 1);
        s.group = malloc(strlen(group) + 1);
        s.grades = malloc(GRADE_NUM * sizeof(unsigned char));

        if (!s.firstName || !s.lastName || !s.group || !s.grades) {
            return MEMORY_ERROR;
        }

        strcpy(s.firstName, firstName);
        strcpy(s.lastName, lastName);
        strcpy(s.group, group);
        for (size_t i = 0; i < GRADE_NUM; i++)
        {
            s.grades[i] = grades[i];
        }

        Student *tmpData = realloc(students->data, (students->size + 1) * sizeof(Student));
        if (!tmpData) {
            return MEMORY_ERROR;
        }
        
        students->data = tmpData;

        students->data[students->size++] = s;
    }

    return OK;
}

void freeStudents(Students *students) {
    for (size_t i = 0; i < students->size; i++)
    {
        free(students->data[i].firstName);
        free(students->data[i].lastName);
        free(students->data[i].group);
        free(students->data[i].grades);
    }
    free(students->data);
    students->size = 0;    
}

void printStudentData(Student *student) {
    if (student == NULL) {
        printf("Такого студента нет\n");
        return;
    }
    printf("Студент: id: %u; имя: %s; фамилия: %s; группа: %s; оценки: ", 
        student->id, student->firstName, student->lastName, student->group);
    for (size_t i = 0; i < GRADE_NUM; i++)
    {
        printf("%c ", student->grades[i]);
    }
    printf("\n");
}

double calcGradesAverage(unsigned char *grades) {
    double s = 0;
    for (size_t i = 0; i < GRADE_NUM; i++)
    {
        s += grades[i];
    }
    return s / GRADE_NUM;
}