#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/studentFind.h"
#include "../include/studentPrint.h"


void printStudentsWithID(Students *students, unsigned int id) {
    int startIndex = 0;
    int curIndex = 0;
    while (true) {
        curIndex = findById(students, id, startIndex);
        if (curIndex < 0) {
            break;
        }
        printStudentData(&(students->data[curIndex]));
        startIndex = curIndex + 1;
    }
    if (startIndex == 0) {
        printf("Студентов не найдено\n");
    }
}

void printStudentsWithStringField(Students *students, char *field, int (*findBy)(Students * students, char *field, size_t startIndex)) {
    int startIndex = 0;
    int curIndex = 0;
    while (true) {
        curIndex = findBy(students, field, startIndex);
        if (curIndex < 0) {
            break;
        }
        printStudentData(&(students->data[curIndex]));
        startIndex = curIndex + 1;
    }
    if (startIndex == 0) {
        printf("Студентов не найдено\n");
    }
}

void printStudentsWithLastName(Students *students, char *lastName) {
    printStudentsWithStringField(students, lastName, findByLastName);
}

void printStudentsWithFirstName(Students *students, char *firstName) {
    printStudentsWithStringField(students, firstName, findByFirstName);
}

void printStudentsWithGroup(Students *students, char *group) {
    printStudentsWithStringField(students, group, findByGroup);
}

void printAllStudents(Students *students) {
    for (size_t i = 0; i < students->size; i++)
    {
        printStudentData(&(students->data[i]));
    }   
}