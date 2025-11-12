#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFINE_HEAP(HEAP_TYPE) \
/* Бинарная куча (минимальная по умолчанию) */\
typedef struct {\
    HEAP_TYPE *data; /* массив элементов */\
    size_t size;     /* текущее количество элементов */\
    size_t capacity; /* вместимость */\
    HEAP_TYPE (*CopyVoidPtr)(const HEAP_TYPE);\
    void (*DeleteVoidPtr)(HEAP_TYPE);\
    int (*CompareVoidPtr)(HEAP_TYPE, HEAP_TYPE);\
} Heap;\
\
static inline void sift_down(Heap *h, size_t index) {\
    size_t new_index = index;\
    HEAP_TYPE value = h->data[index];\
\
    while (true) {\
        size_t child1 = index * 2 + 1;\
        size_t child2 = child1 + 1;\
        if (child1 >= h->size) {\
            break;\
        } else if (child2 >= h->size) {\
            new_index = child1;\
        } else if (h->CompareVoidPtr(h->data[child1], h->data[child2]) <= 0) {\
            new_index = child1;\
        } else {\
            new_index = child2;\
        }\
\
        if (h->CompareVoidPtr(h->data[new_index], value) >= 0)\
            break;\
\
        h->data[index] = h->data[new_index];\
        index = new_index;\
    }\
    h->data[index] = value;\
}\
/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ----------------- */\
/* Создание кучи */\
static inline Heap create_heap(size_t initial_capacity, HEAP_TYPE (*CopyFunc)(const HEAP_TYPE),\
                 void (*DeleteFunc)(HEAP_TYPE),\
                 int (*CompareFunc)(HEAP_TYPE, HEAP_TYPE)) {\
    Heap h = {0};\
    if (initial_capacity == 0) {\
        initial_capacity = 1;\
    }\
    h.CopyVoidPtr = CopyFunc;\
    h.DeleteVoidPtr = DeleteFunc;\
    h.CompareVoidPtr = CompareFunc;\
\
    h.data = (HEAP_TYPE *)malloc(initial_capacity * sizeof(HEAP_TYPE));\
    if (!h.data) {\
        return h;\
    }\
    h.size = 0;\
    h.capacity = initial_capacity;\
    return h;\
}\
\
/* Удаление кучи и освобождение памяти */\
static inline void delete_heap(Heap *h) {\
    if (h->data) {\
        if (h->DeleteVoidPtr) {\
            for (size_t i = 0; i < h->size; i++) {\
                h->DeleteVoidPtr(h->data[i]);\
            }\
        }\
        free(h->data);\
        h->data = NULL;\
    }\
    h->size = 0;\
    h->capacity = 0;\
    h->CopyVoidPtr = NULL;\
    h->DeleteVoidPtr = NULL;\
    h->CompareVoidPtr = NULL;\
}\
\
/* Проверка, пуста ли куча (1 — пуста, 0 — нет) */\
static inline int is_empty_heap(const Heap *h) { return h->size == 0; }\
\
/* Возврат текущего количества элементов */\
static inline size_t size_heap(const Heap *h) { return h->size; }\
\
/* Получение элемента с наивысшим приоритетом (минимального) без удаления */\
static inline HEAP_TYPE peek_heap(const Heap *h) {\
    if (h->size == 0) {\
        abort();\
    }\
    return h->data[0];\
}\
\
/* Добавление элемента в кучу */\
static inline void push_heap(Heap *h, HEAP_TYPE value) {\
    if (h->size >= h->capacity) {\
        size_t new_capacity = h->capacity == 0 ? 1 : h->capacity * 2;\
        HEAP_TYPE *data =\
            (HEAP_TYPE *)realloc(h->data, new_capacity * sizeof(HEAP_TYPE));\
        if (!data) {\
            abort();\
        }\
        h->data = data;\
        h->capacity = new_capacity;\
    }\
    size_t index = h->size++;\
    h->data[index] = h->CopyVoidPtr(value);\
    while (index > 0) {\
        size_t parent = (index - 1) / 2;\
        if (h->CompareVoidPtr(h->data[parent], h->data[index]) <= 0) {\
            return;\
        }\
\
        HEAP_TYPE tmp = h->data[parent];\
        h->data[parent] = h->data[index];\
        h->data[index] = tmp;\
        index = parent;\
    }\
}\
\
/* Удаление элемента с наивысшим приоритетом (минимального) и возврат его */\
static inline HEAP_TYPE pop_heap(Heap *h) {\
    if (h->size == 0) {\
        abort();\
    }\
\
    HEAP_TYPE min_element = h->data[0];\
    h->size--;\
    if (h->size == 0) {\
        return min_element;\
    }\
    h->data[0] = h->data[h->size];\
    sift_down(h, 0);\
    return min_element;\
}\
\
/* Построение кучи из массива */\
static inline Heap build_heap(const HEAP_TYPE *array, size_t n,\
                HEAP_TYPE (*CopyFunc)(const HEAP_TYPE), void (*DeleteFunc)(HEAP_TYPE),\
                int (*CompareFunc)(HEAP_TYPE, HEAP_TYPE)) {\
    Heap h = create_heap(n, CopyFunc, DeleteFunc, CompareFunc);\
    if (!h.data) {\
        return h;\
    }\
\
    for (size_t i = 0; i < n; i++) {\
        h.data[i] = h.CopyVoidPtr(array[i]);\
    }\
    h.size = n;\
\
    for (size_t i = (n / 2); i-- > 0;) {\
        sift_down(&h, i);\
    }\
\
    return h;\
}\
\
/* Сравнение двух куч (лексикографически по массиву внутреннего представления)*/\
/* возвращает 1 — равны, 0 — не равны */\
static inline int is_equal_heap(const Heap *h1, const Heap *h2) {\
    if (h1 == h2)\
        return 1;\
    if (!h1 || !h2)\
        return 0;\
    if (h1->size != h2->size)\
        return 0;\
\
    for (size_t i = 0; i < h1->size; i++) {\
        if (h1->CompareVoidPtr(h1->data[i], h2->data[i]) != 0) {\
            return 0;\
        }\
    }\
    return 1;\
}\

#endif // HEAP_H