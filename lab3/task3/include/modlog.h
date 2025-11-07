#ifndef MODLOG_H
#define MODLOG_H

#include "linkedList.h"
#include "liver.h"
#include <stdbool.h>

typedef enum {
    MOD_ADD,
    MOD_DELETE,
    MOD_UPDATE
} ModType;

typedef struct {
    ModType type;
    Liver before;
    Liver after;
    bool keep_sorted_by_age;
} ModRecord;

typedef struct {
    ModRecord *items;
    size_t size;
    size_t capacity;
} ModLog;

void modlog_init(ModLog *log);
void modlog_free(ModLog *log);
void modlog_log_add(ModLog *log, const Liver *inserted, bool keep_sorted_by_age);
void modlog_log_delete(ModLog *log, const Liver *deleted, bool keep_sorted_by_age);
void modlog_log_update(ModLog *log, const Liver *before, const Liver *after);

size_t modlog_undo_last_half(ModLog *log, LinkedList *list);

#endif
