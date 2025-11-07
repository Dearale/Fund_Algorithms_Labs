#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "../include/liver_ops.h"
#include "../include/modlog.h"


int cmp_birthdate(BirthDate a, BirthDate b) {
    if (a.year != b.year) 
        return a.year - b.year;
    if (a.month != b.month) 
        return a.month - b.month;
    if (a.day != b.day) 
        return a.day - b.day;
    return 0;
}

int compare_age(Liver a, Liver b) {
    return cmp_birthdate(a.birthDate, b.birthDate);
}

Liver copy_resident(Liver liver) {
    return liver;
}

void delete_resident(Liver liver) {
    (void)liver;
}

Liver get_invalid_resident() {
    Liver liver;
    liver.id = SIZE_MAX;
    return liver;
}

int compare_residents(Liver a, Liver b) {
    if (a.id != b.id) {
        return (a.id < b.id) ? -1 : 1;
    }
    int res = 0;
    if ((res = strcmp(a.last_name, b.last_name))) return res;
    if ((res = strcmp(a.first_name, b.first_name))) return res;
    if ((res = strcmp(a.second_name, b.second_name))) return res;

    if (a.birthDate.year != b.birthDate.year) 
        return a.birthDate.year - b.birthDate.year;
    if (a.birthDate.month != b.birthDate.month)
        return a.birthDate.month - b.birthDate.month;
    if (a.birthDate.day != b.birthDate.day)
        return a.birthDate.day - b.birthDate.day;

    if (a.gender != b.gender)
        return a.gender - b.gender;

    if (a.income < b.income) return -1;
    if (a.income > b.income) return 1;
    return 0;
}


LinkedList create_resident_list() {
    return create_list(delete_resident, copy_resident, compare_residents, get_invalid_resident());
}


int liver_matches(const Liver* l, const LiverQuery* q) {
    if (!l || !q) return 0;
    if (q->set_id && l->id != q->id) return 0;
    if (q->set_last && strcmp(l->last_name,  q->last_name) != 0) return 0;
    if (q->set_first && strcmp(l->first_name, q->first_name) != 0) return 0;
    if (q->set_second && strcmp(l->second_name,q->second_name)!= 0) return 0;
    if (q->set_gender && toupper((unsigned char)l->gender) != toupper((unsigned char)q->gender)) return 0;
    if (q->set_birth_from && cmp_birthdate(l->birthDate, q->birth_from) < 0) return 0;
    if (q->set_birth_to && cmp_birthdate(l->birthDate, q->birth_to) > 0) return 0;
    if (q->set_income_min && l->income < q->income_min) return 0;
    if (q->set_income_max && l->income > q->income_max) return 0;
    return 1;
}

int find_first_index(const LinkedList* list, const LiverQuery* q, size_t* out_index) {
    size_t i = 0;
    for (Node *n = list->head; n; n = n->next) {
        if (liver_matches(n->data, q)) {
            *out_index = i;
            return 1;
        }
        i++;
    }
    return 0;
}

size_t find_all_indices(const LinkedList* list, const LiverQuery* q, size_t* indices, size_t max_indices) {
    size_t i = 0;
    size_t found = 0;
    for (Node* n = list->head; n; n = n->next) {
        if (liver_matches(n->data, q)) {
            if (found < max_indices)
                indices[found] = i;
            found++;
        }
        i++;
    }
    return found;
}

bool contains_id(const LinkedList* list, size_t id) {
    size_t i = 0;
    for (Node* n = list->head; n; n = n->next, ++i) {
        if (n->data->id == id) {
            return true;
        }
    }
    return false;
}

int find_index_by_id(const LinkedList* list, size_t id, size_t* out_index) {
    size_t i = 0;
    for (Node* n = list->head; n; n = n->next, ++i) {
        if (n->data->id == id) {
            if (out_index) *out_index = i;
            return 1;
        }
    }
    return 0;
}

bool add_resident(LinkedList* list, const Liver* value, bool keep_sorted_by_age, ModLog *log) {
    if (contains_id(list, value->id)) {
        return false;
    }
    if (keep_sorted_by_age) {
        insert_sorted_by_age(list, value);
    }
    else {
        push_back_list(list, *value);
    }
    if (log)
        modlog_log_add(log, value, keep_sorted_by_age);

    return true;
}

int remove_by_id(LinkedList* list, size_t id, bool keep_sorted_by_age, ModLog *log) {
    size_t i = 0;
    for (Node* n = list->head; n; n = n->next, ++i) {
        if (n->data->id == id) {
            Liver data = get_at_list(list, i);
            if (log)
                modlog_log_delete(log, &data, keep_sorted_by_age);
            delete_at_list(list, i);
            return 1;
        }
    }
    return 0;
}

int update_by_id(LinkedList* list, size_t id, const Liver* new_value, bool keep_sorted_by_age, ModLog *log) {
    size_t i = 0;
    for (Node* n = list->head; n; n = n->next, ++i) {
        if (n->data->id == id) {
            Liver before = get_at_list(list, i);
            delete_at_list(list, i);
            if (keep_sorted_by_age)
                insert_sorted_by_age(list, new_value);
            else {
                if (i > list->size)
                    i = list->size;
                insert_at_list(list, i, *new_value);
            }
            if (log)
                modlog_log_update(log, &before, new_value);
            return 1;
        }
    }
    return 0;
}

Status save_residents_to_file(const char* path, const LinkedList* list) {
    FILE * fout = fopen(path, "w");
    if (!fout) {
        return COULDNT_OPEN_FILE;
    }

    for (Node *n = list->head; n; n = n->next) {
        const Liver* lv = n->data;
        fprintf(fout, "%zu %s %s ", lv->id, lv->last_name, lv->first_name);
        if (lv->second_name[0] != '\0') {
            fprintf(fout, "%s ", lv->second_name);
        }
        fprintf(fout, "%d %d %d %c %.2f\n",
                lv->birthDate.day, lv->birthDate.month, lv->birthDate.year,
                lv->gender,
                lv->income);
    }

    fclose(fout);

    return OK;
}

void insert_sorted_by_age(LinkedList *residents, const Liver *l) {
    size_t i = 0;
    for (Node *cur = residents->head; cur; cur = cur->next) {
        if (compare_age(*l, (*cur->data)) > 0) {
            insert_at_list(residents, i, *l);
            return;
        }
        i++;
    }

    push_back_list(residents, *l);
}

void sort_list_by_age(LinkedList* list) {
    if (!list || list->size < 2) return;

    /* создаём временный список с теми же колбэками */
    LinkedList tmp = create_resident_list();

    for (Node* n = list->head; n; n = n->next) {
        insert_sorted_by_age(&tmp, n->data);
    }

    erase_list(list);
    list->head = tmp.head;
    list->tail = tmp.tail;
    list->size = tmp.size;

    tmp.head = tmp.tail = NULL;
    tmp.size = 0;
}
