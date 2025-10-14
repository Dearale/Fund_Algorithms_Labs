#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/studentFind.h"

int findById(Students *students, unsigned int id, size_t startIndex) {
    for (size_t i = startIndex; i < students->size; i++)
    {
        if (students->data[i].id == id) {
            return i;
        }
    }
    return -1;
}

int findByStringField(Students *students, char *field, bool (*equals)(Student *, char *), size_t startIndex) {
    for (size_t i = startIndex; i < students->size; i++)
    {
        if (equals(&(students->data[i]), field)) {
            return i;
        }
    }
    return -1;
}

bool equalsFirstName(Student * student, char * firstName) { return strcmp(student->firstName, firstName) == 0; }
bool equalsLastName(Student * student, char * lastName) { return strcmp(student->lastName, lastName) == 0; }
bool equalsGroup(Student * student, char * group) { return strcmp(student->group, group) == 0; }

int findByFirstName(Students *students, char *firstName, size_t startIndex) {
    return findByStringField(students, firstName, equalsFirstName, startIndex);
}

int findByLastName(Students *students, char *lastName, size_t startIndex) {
    return findByStringField(students, lastName, equalsLastName, startIndex);
}

int findByGroup(Students *students, char *group, size_t startIndex) {
    return findByStringField(students, group, equalsGroup, startIndex);
}