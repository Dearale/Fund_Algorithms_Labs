#include "../include/modlog.h"
#include "../include/liver_ops.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ensure_capacity(ModLog *log, size_t need) {
    if (log->capacity >= need)
        return 1;

    size_t newcap = log->capacity ? log->capacity * 2 : 16;
    if (newcap < need)
        newcap = need;

    ModRecord *p = (ModRecord*)realloc(log->items, newcap * sizeof(ModRecord));
    if (!p)
        return 0;
    log->items = p;
    log->capacity = newcap;
    return 1;
}

void modlog_init(ModLog *log) {
    log->items = NULL;
    log->size = 0;
    log->capacity = 0;
}

void modlog_free(ModLog *log) {
    free(log->items);
    log->items = NULL;
    log->size = log->capacity = 0;
}

void push_record(ModLog *log, const ModRecord *r) {
    if (ensure_capacity(log, log->size + 1)) {
        log->items[log->size++] = *r;
    }
}

void modlog_log_add(ModLog *log, const Liver *inserted, bool keep_sorted_by_age) {
    ModRecord r;
    r.type = MOD_ADD;
    r.after = *inserted;
    r.keep_sorted_by_age = keep_sorted_by_age;
    push_record(log, &r);
}

void modlog_log_delete(ModLog *log, const Liver *deleted, bool keep_sorted_by_age) {
    ModRecord r;
    r.type = MOD_DELETE;
    r.before = *deleted;
    r.keep_sorted_by_age = keep_sorted_by_age;
    push_record(log, &r);
}

void modlog_log_update(ModLog *log, const Liver *before, const Liver *after) {
    ModRecord r;
    r.type = MOD_UPDATE;
    r.before = *before;
    r.after  = *after;
    r.keep_sorted_by_age = 1;
    push_record(log, &r);
}

size_t modlog_undo_last_half(ModLog *log, LinkedList *list) {
    size_t undone = 0;
    for (size_t i = 0; i < log->size / 2; ++i) {
        ModRecord *rec = &log->items[log->size - 1 - i];
        switch (rec->type) {
            case MOD_ADD: {
                remove_by_id(list, rec->after.id, rec->keep_sorted_by_age, NULL);
            } break;
            case MOD_DELETE: {
                add_resident(list, &rec->before, rec->keep_sorted_by_age, NULL);
            } break;
            case MOD_UPDATE: {
                update_by_id(list, rec->before.id, &rec->before, rec->keep_sorted_by_age, NULL);
            } break;
            default: 
                break;
        }
        ++undone;
    }
    log->size = 0;

    return undone;
}
