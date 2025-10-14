#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

typedef enum {
    OK,
    LINE_OUT_OF_BOUNDS,
    MEMORY_ERROR,
    STUDENT_WITH_ID_NOT_FOUND,
    COULDNT_OPEN_FILE,
} Status;

void printStatus(Status status);

#endif