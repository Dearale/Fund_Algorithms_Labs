#ifndef STUDENT_PRINT_H
#define STUDENT_PRINT_H

void printStudentsWithID(Students *students, unsigned int id);

void printStudentsWithStringField(Students *students, char *field, int (*findBy)(Students * students, char *field, size_t startIndex));

void printStudentsWithLastName(Students *students, char *lastName);

void printStudentsWithFirstName(Students *students, char *firstName);

void printStudentsWithGroup(Students *students, char *group);

void printAllStudents(Students *students);


#endif