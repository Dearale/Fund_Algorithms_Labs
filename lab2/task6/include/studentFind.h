#ifndef STUDENT_FIND_H
#define STUDENT_FIND_H

int findById(Students *students, unsigned int id, size_t startIndex);

int findByStringField(Students *students, char *field, bool (*equals)(Student *, char *), size_t startIndex);

bool equalsFirstName(Student * student, char * firstName);
bool equalsLastName(Student * student, char * lastName);
bool equalsGroup(Student * student, char * group);

int findByFirstName(Students *students, char *firstName, size_t startIndex);

int findByLastName(Students *students, char *lastName, size_t startIndex);

int findByGroup(Students *students, char *group, size_t startIndex);

#endif