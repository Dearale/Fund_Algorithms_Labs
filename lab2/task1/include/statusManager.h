#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

typedef enum {
    OK,
    NUMBER_OUT_OF_BOUNDS,
    BASE_OUT_OF_BOUNDS,
    MEMORY_ERROR,
} Status;

void printStatus(Status status);

#endif