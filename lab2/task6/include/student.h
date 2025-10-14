#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include "student.h"
#include "statusManager.h"
#include "utils.h"

#define MAX_STRING 200
#define GRADE_NUM 5

typedef struct {
    unsigned int id;
    char *firstName;
    char *lastName;
    char *group;
    unsigned char *grades;
} Student;

typedef struct {
    Student *data;
    size_t size;
} Students;


Status readStudents(FILE * fin, Students *students);
void freeStudents(Students *students);

void printStudentData(Student *student);


double calcGradesAverage(unsigned char *grades);

#endif