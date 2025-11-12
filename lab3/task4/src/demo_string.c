#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"

DEFINE_HEAP(char*)

static char* str_copy(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* p = (char*)malloc(len + 1);
    if (!p) {
        fprintf(stderr, "Ошибка: не удалось выделить память для копии строки.\n");
        abort();
    }
    memcpy(p, s, len + 1);
    return p;
}

static void str_destroy(char* s) {
    free(s);
}

static int str_compare(char* a, char* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    return strcmp(a, b);
}

// Печать содержимого кучи
static void print_heap(const Heap *h, const char *title) {
    printf("%s (размер=%zu, вместимость=%zu): [", title, h->size, h->capacity);
    for (size_t i = 0; i < h->size; i++) {
        printf("\"%s\"%s", h->data[i], (i + 1 < h->size) ? ", " : "");
    }
    printf("]\n");
}

/* === Демонстрация create_heap и is_empty_heap === */
static void demo_create_and_empty(void) {
    printf("\n=== Демонстрация: создание кучи и проверка пустоты ===\n");
    Heap h = create_heap(5, str_copy, str_destroy, str_compare);
    print_heap(&h, "После создания");
    printf("Пуста ли куча? %s\n", is_empty_heap(&h) ? "Да" : "Нет");
    delete_heap(&h);
}

/* === Демонстрация push_heap и peek_heap === */
static void demo_push_and_peek(void) {
    printf("\n=== Демонстрация: добавление элементов и просмотр вершины ===\n");
    Heap h = create_heap(2, str_copy, str_destroy, str_compare);
    const char* values[] = {"груша", "яблоко", "апельсин", "банан", "абрикос"};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        printf("Добавляем элемент \"%s\"...\n", values[i]);
        push_heap(&h, (char*)values[i]);
        print_heap(&h, "Куча после вставки");
        printf("Минимальный элемент сейчас: \"%s\"\n", peek_heap(&h));
    }
    delete_heap(&h);
}

/* === Демонстрация pop_heap === */
static void demo_pop(void) {
    printf("\n=== Демонстрация: удаление элементов (pop_heap) ===\n");
    const char* arr[] = {"арбуз", "дыня", "вишня", "яблоко", "груша", "слива"};
    Heap h = build_heap(arr, sizeof(arr) / sizeof(arr[0]),
                        str_copy, str_destroy, str_compare);
    print_heap(&h, "Построенная куча");
    printf("Извлекаем элементы в порядке возрастания:\n");
    while (!is_empty_heap(&h)) {
        char* s = pop_heap(&h);
        printf("\"%s\"\n", s);
        free(s);
        print_heap(&h, "Куча после извлечения");
    }
    printf("\n");
    delete_heap(&h);
}

/* === Демонстрация build_heap === */
static void demo_build(void) {
    printf("\n=== Демонстрация: построение кучи из массива ===\n");
    const char* arr[] = {"дельта", "альфа", "чарли", "браво", "эхо"};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("\"%s\" ", arr[i]);
    }
    printf("\n");
    Heap h = build_heap(arr, sizeof(arr) / sizeof(arr[0]),
                        str_copy, str_destroy, str_compare);
    print_heap(&h, "После build_heap");
    delete_heap(&h);
}

/* === Демонстрация size_heap === */
static void demo_size(void) {
    printf("\n=== Демонстрация: размер кучи ===\n");
    Heap h = create_heap(1, str_copy, str_destroy, str_compare);
    printf("Текущий размер: %zu\n", size_heap(&h));
    const char* vals[] = {"з", "е", "д", "г", "в"};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        push_heap(&h, (char*)vals[i]);
        printf("После добавления \"%s\" размер = %zu\n", vals[i], size_heap(&h));
    }
    delete_heap(&h);
}

/* === Демонстрация is_equal_heap === */
static void demo_equal(void) {
    printf("\n=== Демонстрация: сравнение куч ===\n");
    const char* a[] = {"кот", "пёс", "птица"};
    const char* b[] = {"кот", "пёс", "птица"};
    const char* c[] = {"кот", "пёс", "медведь"};

    Heap h1 = build_heap(a, 3, str_copy, str_destroy, str_compare);
    Heap h2 = build_heap(b, 3, str_copy, str_destroy, str_compare);
    Heap h3 = build_heap(c, 3, str_copy, str_destroy, str_compare);

    print_heap(&h1, "Куча h1");
    print_heap(&h2, "Куча h2");
    print_heap(&h3, "Куча h3");

    printf("Кучи h1 и h2 равны? %s\n", is_equal_heap(&h1, &h2) ? "Да" : "Нет");
    printf("Кучи h1 и h3 равны? %s\n", is_equal_heap(&h1, &h3) ? "Да" : "Нет");

    delete_heap(&h1);
    delete_heap(&h2);
    delete_heap(&h3);
}

/* === Демонстрация delete_heap === */
static void demo_delete(void) {
    printf("\n=== Демонстрация: удаление всей кучи ===\n");
    Heap h = create_heap(3, str_copy, str_destroy, str_compare);
    push_heap(&h, "альфа");
    push_heap(&h, "бета");
    print_heap(&h, "Перед удалением");
    delete_heap(&h);
    printf("После delete_heap: размер = %zu, вместимость = %zu\n", h.size, h.capacity);
}

/* === Главная функция === */
int main(void) {
    demo_create_and_empty();
    demo_push_and_peek();
    demo_pop();
    demo_build();
    demo_size();
    demo_equal();
    demo_delete();
    return 0;
}
