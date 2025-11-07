#ifndef LIVER_OPS_H
#define LIVER_OPS_H

#include <stdbool.h>
#include "linkedList.h"
#include "liver.h"
#include "modlog.h"

typedef struct {
    int set_id; size_t id;
    int set_last; char last_name[MAX_STR_LEN];
    int set_first; char first_name[MAX_STR_LEN];
    int set_second; char second_name[MAX_STR_LEN];
    int set_gender; char gender;
    int set_birth_from; BirthDate birth_from;
    int set_birth_to; BirthDate birth_to;
    int set_income_min; double income_min;
    int set_income_max; double income_max;
} LiverQuery;

LinkedList create_resident_list();

int cmp_birthdate(BirthDate a, BirthDate b);

int liver_matches(const Liver* lv, const LiverQuery* q);

int find_first_index(const LinkedList* list, const LiverQuery* q, size_t* out_index);

size_t find_all_indices(const LinkedList* list, const LiverQuery* q, size_t* indices, size_t max_indices);

bool add_resident(LinkedList* list, const Liver* value, bool keep_sorted_by_age, ModLog *log);

int remove_by_id(LinkedList* list, size_t id, bool keep_sorted_by_age, ModLog *log);

int update_by_id(LinkedList* list, size_t id, const Liver* new_value, bool keep_sorted_by_age, ModLog *log);

Status save_residents_to_file(const char* path, const LinkedList* list);

void insert_sorted_by_age(LinkedList *residents, const Liver *l);

void sort_list_by_age(LinkedList* list);

bool contains_id(const LinkedList* list, size_t id);

int find_index_by_id(const LinkedList* list, size_t id, size_t* out_index);

#endif
