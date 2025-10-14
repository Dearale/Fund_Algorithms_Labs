#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/studentCompare.h"
#include "../include/studentFind.h"
#include "../include/studentPrint.h"
#include "../include/statusManager.h"


Status trySaveStudentByID(Students *students, unsigned int id, const char *filePath) {
    FILE * fout = fopen(filePath, "a");
    if (!fout) {
        return COULDNT_OPEN_FILE;
    }

    int index = findById(students, id, 0);
    if (index < 0) {
        return STUDENT_WITH_ID_NOT_FOUND;
    }
    Student *student = &(students->data[index]);
    double avg = calcGradesAverage(student->grades);
    fprintf(fout, "%s %s %s %.2f\n", student->firstName, student->lastName, student->group, avg);
    fclose(fout);
    return OK;
}

Status saveBestStudents(Students *students, const char *filePath) {
    FILE * fout = fopen(filePath, "a");
    if (!fout) {
        return COULDNT_OPEN_FILE;
    }

    double s = 0;
    for (size_t i = 0; i < students->size; i++)
    {
        s += calcGradesAverage(students->data[i].grades);
    }

    double globalAvg = s / students->size;

    for (size_t i = 0; i < students->size; i++)
    {
        double avg = calcGradesAverage(students->data[i].grades);
        if (avg > globalAvg) {
            fprintf(fout, "%s %s\n", students->data[i].lastName, students->data[i].firstName);
        }
    }
    fclose(fout);
    return OK;
}
