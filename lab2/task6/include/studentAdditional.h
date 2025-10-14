#ifndef STUDENT_ADDITIONAL_H
#define STUDENT_ADDITIONAL_H

#include <stdio.h>

#include "statusManager.h"
#include "student.h"

Status trySaveStudentByID(Students *students, unsigned int id, const char *filePath);

Status saveBestStudents(Students *students, const char *filePath);

#endif