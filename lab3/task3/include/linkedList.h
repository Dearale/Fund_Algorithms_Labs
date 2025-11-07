#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

#define DEFINE_LINKED_LIST(LIST_TYPE)\
/* Узел двусвязного списка*/\
typedef struct Node {\
    LIST_TYPE* data;\
    struct Node *prev;\
    struct Node *next;\
} Node;\
\
/* Двусвязный список*/\
typedef struct {\
    Node *head;\
    Node *tail;\
    size_t size;\
    void (*DeleteVoidPtr)(LIST_TYPE);\
    LIST_TYPE (*CopyVoidPtr)(LIST_TYPE);\
    int (*Compare)(LIST_TYPE, LIST_TYPE);\
    LIST_TYPE invalidData;\
} LinkedList;\
\
/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ---------------- */\
/* Создание пустого списка */\
static inline LinkedList create_list(void (*DeleteVoidPtr)(LIST_TYPE), LIST_TYPE (*CopyVoidPtr)(LIST_TYPE), int (*Compare)(LIST_TYPE, LIST_TYPE), LIST_TYPE invalidData) {\
    LinkedList l;\
    l.head = NULL;\
    l.tail = NULL;\
    l.size = 0;\
    l.DeleteVoidPtr = DeleteVoidPtr;\
    l.CopyVoidPtr = CopyVoidPtr;\
    l.Compare = Compare;\
    l.invalidData = invalidData;\
    return l;\
}\
\
static inline Node *create_node(LinkedList *list, LIST_TYPE value) {\
    Node *node = (Node *)malloc(sizeof(Node));\
    if (!node) {\
        return NULL;\
    }\
    node->data = (LIST_TYPE*)malloc(sizeof(LIST_TYPE));\
    if (!node->data) {\
        free(node);\
        return NULL;\
    }\
\
    *(node->data) = list->CopyVoidPtr(value);\
    node->prev = node->next = NULL;\
    return node;\
}\
\
static inline void destroy_node(LinkedList *list, Node *node) {\
    if (node->data) {\
        list->DeleteVoidPtr(*(node->data));\
        free(node->data);\
    }\
    node->prev = node->next = NULL;\
    free(node);\
}\
\
static inline Node* get_node_at(const LinkedList *list, size_t index) {\
    if (index >= list->size)\
        return NULL;\
\
    Node *found;\
    if (index < list->size / 2) {\
        found = list->head;\
        for (size_t i = 0; i < index; i++) {\
            found = found->next;\
        }\
    } else {\
        found = list->tail;\
        for (size_t i = list->size - 1; i > index; i--) {\
            found = found->prev;\
        }\
    }\
    return found;\
}\
\
/* Добавление элемента в конец списка */\
static inline void push_back_list(LinkedList *list, LIST_TYPE value) {\
    Node *n = create_node(list, value);\
    if (!n) {\
        return;\
    }\
    if (!list->tail) {\
        list->head = list->tail = n;\
    } else {\
        n->prev = list->tail;\
        list->tail->next = n;\
        list->tail = n;\
    }\
    list->size++;\
}\
/* Добавление элемента в начало списка */\
static inline void push_front_list(LinkedList *list, LIST_TYPE value) {\
    Node *n = create_node(list, value);\
    if (!n) {\
        return;\
    }\
\
    if (!list->head) {\
        list->head = list->tail = n;\
    } else {\
        n->next = list->head;\
        list->head->prev = n;\
        list->head = n;\
    }\
    list->size++;\
}\
\
/* Удаление элемента с конца списка */\
static inline LIST_TYPE pop_back_list(LinkedList *list) {\
    Node *tail = list->tail;\
    LIST_TYPE data = *(tail->data);\
    tail->data = NULL;\
    if (list->head == list->tail) {\
        list->head = list->tail = NULL;\
    } else {\
        list->tail = tail->prev;\
        list->tail->next = NULL;\
    }\
    destroy_node(list, tail);\
    list->size--;\
    return data;\
}\
/* Удаление элемента с начала списка */\
static inline LIST_TYPE pop_front_list(LinkedList *list) {\
    Node *head = list->head;\
    LIST_TYPE data = *(head->data);\
    head->data = NULL;\
    if (list->head == list->tail) {\
        list->head = list->tail = NULL;\
    } else {\
        list->head = head->next;\
        list->head->prev = NULL;\
    }\
    destroy_node(list, head);\
    list->size--;\
    return data;\
}\
/* Очистка содержимого списка (удаление всех элементов) */\
static inline void erase_list(LinkedList *list) {\
    while (list->head) {\
        Node *next = list->head->next;\
        destroy_node(list, list->head);\
        list->head = next;\
    }\
    list->head = list->tail = NULL;\
    list->size = 0;\
}\
/* Полное удаление списка (освобождение ресурсов) */\
static inline void delete_list(LinkedList *list) {\
    erase_list(list);\
}\
/* Вставка элемента по индексу */\
static inline void insert_at_list(LinkedList *list, size_t index, LIST_TYPE value) {\
    if (index > list->size) {\
        return;\
    }\
    if (index == 0) {\
        push_front_list(list, value);\
        return;\
    }\
    if (index == list->size) {\
        push_back_list(list, value);\
        return;\
    }\
\
    Node *node = get_node_at(list, index);\
\
    Node *new_node = create_node(list, value);\
    new_node->next = node;\
    new_node->prev = node->prev;\
    new_node->prev->next = new_node;\
    node->prev = new_node;\
    list->size++;\
}\
/* Удаление элемента по индексу */\
static inline void delete_at_list(LinkedList *list, size_t index) {\
    if (index > list->size) {\
        return;\
    }\
    if (index == 0) {\
        LIST_TYPE data = pop_front_list(list);\
        list->DeleteVoidPtr(data);\
        return;\
    }\
    if (index == list->size - 1) {\
        LIST_TYPE data = pop_back_list(list);\
        list->DeleteVoidPtr(data);\
        return;\
    }\
\
    Node *node = get_node_at(list, index);\
    node->prev->next = node->next;\
    node->next->prev = node->prev;\
    destroy_node(list, node);\
    list->size--;\
}\
/* Получение элемента по индексу */\
static inline LIST_TYPE get_at_list(const LinkedList *list, size_t index) {\
    Node *n = get_node_at(list, index);\
    if (!n) {\
        return list->invalidData;\
    }\
\
    return *(n->data);\
}\
\
/* Сравнение двух списков (лексикографически) */\
/* возвращает 1 — равны, 0 — не равны */\
static inline int is_equal_list(const LinkedList *l1, const LinkedList *l2) {\
    if (l1 == l2) return 1;\
    if (!l1 || !l2) return 0;\
    if (l1->size != l2->size) return 0;\
\
    Node *head1 = l1->head;\
    Node *head2 = l2->head;\
    while (head1 && head2) {\
        if (l1->Compare(*(head1->data), *(head2->data)) != 0) {\
            return 0;\
        }\
        head1 = head1->next;\
        head2 = head2->next;\
    }\
    return 1;\
}\
\
/* ----------------- СТЕК ----------------- */\
/* Поместить элемент на вершину стека */\
static inline void push_stack(LinkedList *stack, LIST_TYPE value) {\
    push_back_list(stack, value);\
}\
/* Извлечь элемент с вершины стека */\
static inline LIST_TYPE pop_stack(LinkedList *stack) {\
    return pop_back_list(stack);\
}\
/* Получить элемент с вершины стека без удаления */\
static inline LIST_TYPE peek_stack(const LinkedList *stack) {\
    return *(stack->tail->data);\
}\
\
/* ----------------- ОЧЕРЕДЬ ----------------- */\
/* Добавить элемент в очередь */\
static inline void enqueue(LinkedList *queue, LIST_TYPE value) {\
    push_back_list(queue, value);\
}\
/* Извлечь элемент из очереди */\
static inline LIST_TYPE dequeue(LinkedList *queue) {\
    return pop_front_list(queue);\
}\
/* Получить первый элемент очереди без удаления */\
static inline LIST_TYPE peek_queue(const LinkedList *queue) {\
    return *(queue->head->data);\
}


#endif