#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

typedef enum {
    OK,
    LINE_OUT_OF_BOUNDS,
} Status;

void printStatus(Status status);

#endif