#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFINE_VECTOR(VECTOR_TYPE)\
typedef struct {\
    VECTOR_TYPE *data; \
    size_t size;       \
    size_t capacity;   \
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);\
    void (*DeleteVoidPtr)(VECTOR_TYPE);\
} Vector;\
\
/* Создание нового вектора*/\
Vector create_vector(size_t initial_capacity,\
                     VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),\
                     void (*DeleteFunc)(VECTOR_TYPE)) {\
    Vector vector;\
    vector.capacity = initial_capacity;\
    vector.size = 0;\
    vector.data = NULL;\
    vector.CopyVoidPtr = CopyFunc;\
    vector.DeleteVoidPtr = DeleteFunc;\
    if (initial_capacity == 0) {\
        return vector;\
    }\
\
    vector.data = (VECTOR_TYPE *)malloc(sizeof(VECTOR_TYPE) * initial_capacity);\
    if (!vector.data) {\
        vector.data = NULL;\
        vector.capacity = 0;\
    }\
    return vector;\
}\
\
/* Удаление внутреннего содержимого вектора (data, size=0, capacity=0)*/\
void erase_vector(Vector *v) {\
    if (v->DeleteVoidPtr && v->data) {\
        for (size_t i = 0; i < v->size; i++) {\
            v->DeleteVoidPtr(v->data[i]);\
        }\
    }\
    v->size = 0;\
    v->capacity = 0;\
}\
\
/* Сравнение двух векторов (лексикографически)*/\
/* возвращает 1 — равны, 0 — не равны*/\
int is_equal_vector(const Vector *v1, const Vector *v2) {\
    if (v1->size != v2->size) {\
        return 0;\
    }\
\
    for (size_t i = 0; i < v1->size; i++) {\
        if (v1->data[i] != v2->data[i]) {\
            return 0;\
        }\
    }\
    return 1;\
}\
\
/* Копирование содержимого одного вектора в другой (существующий)*/\
void copy_vector(Vector *dest, const Vector *src) {\
    erase_vector(dest);\
    if (src->size == 0) {\
        return;\
    }\
\
    free(dest->data);\
    dest->data = (VECTOR_TYPE *)malloc(sizeof(VECTOR_TYPE) * src->capacity);\
    if (!dest->data) {\
        return;\
    }\
\
    if (src->CopyVoidPtr) {\
        for (size_t i = 0; i < src->size; i++) {\
            dest->data[i] = src->CopyVoidPtr(src->data[i]);\
        }\
    } else {\
        for (size_t i = 0; i < src->size; i++) {\
            dest->data[i] = src->data[i];\
        }\
    }\
\
    dest->capacity = src->capacity;\
    dest->size = src->size;\
    dest->CopyVoidPtr = src->CopyVoidPtr;\
    dest->DeleteVoidPtr = src->DeleteVoidPtr;\
}\
\
/* Создание нового вектора в динамической памяти и копирование содержимого*/\
Vector *copy_vector_new(const Vector *src) {\
    if (!src) {\
        return NULL;\
    }\
    Vector * newVec = (Vector *)malloc(sizeof(Vector));\
    if (!newVec) {\
        return NULL;\
    }\
\
    *newVec = create_vector(src->capacity, src->CopyVoidPtr, src->DeleteVoidPtr);\
    if (!newVec->data) {\
        free(newVec);\
        return NULL;\
    }\
\
    copy_vector(newVec, src);\
    return newVec;\
}\
\
/* Добавление элемента в конец вектора*/\
void push_back_vector(Vector *v, VECTOR_TYPE value) {\
    if (v->size >= v->capacity) {\
        size_t newCapacity = (v->capacity == 0) ? 1 : v->capacity * 2;\
        VECTOR_TYPE *tmp = (VECTOR_TYPE *)realloc(v->data, sizeof(VECTOR_TYPE) * newCapacity);\
        if (!tmp) {\
            return;\
        }\
        v->data = tmp;\
        v->capacity = newCapacity;\
    }\
    if (v->CopyVoidPtr) {\
        v->data[v->size++] = v->CopyVoidPtr(value);\
    } else {\
        v->data[v->size++] = value;\
    }\
}\
\
/* Удаление элемента по индексу*/\
void delete_at_vector(Vector *v, size_t index) {\
    if (index < v->size) {\
        if (v->DeleteVoidPtr) {\
            v->DeleteVoidPtr(v->data[index]);\
        }\
\
        for (size_t i = index; i < v->size - 1; i++) {\
            v->data[i] = v->data[i + 1];\
        }\
        v->size--;\
    }\
}\
\
/* Получение элемента по индексу*/\
VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {\
    if (index >= v->size) {\
        return (VECTOR_TYPE)0;\
    }\
\
    return v->data[index];\
}\
\
/* Освобождение памяти, занимаемой экземпляром вектора*/\
void delete_vector(Vector *v) {\
    erase_vector(v);\
    free(v->data);\
}
#endif // VECTOR_H