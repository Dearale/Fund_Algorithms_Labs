#include <stdio.h>
#include <stdlib.h>
#include "../include/heap.h"

DEFINE_HEAP(int)

static int int_copy(int x) { return x; }
static void int_destroy(int x) { (void)x; }
static int int_compare(int a, int b) { return (a > b) - (a < b); }

static void print_heap(const Heap *h, const char *title) {
    printf("%s (размер=%zu, вместимость=%zu): [", title, h->size, h->capacity);
    for (size_t i = 0; i < h->size; i++) {
        printf("%d%s", h->data[i], (i + 1 < h->size) ? ", " : "");
    }
    printf("]\n");
}

/* === Демонстрация create_heap и is_empty_heap === */
static void demo_create_and_empty(void) {
    printf("\n=== Демонстрация: создание кучи и проверка пустоты ===\n");
    Heap h = create_heap(5, int_copy, int_destroy, int_compare);
    print_heap(&h, "После создания");
    printf("Пуста ли куча? %s\n", is_empty_heap(&h) ? "Да" : "Нет");
    delete_heap(&h);
}

/* === Демонстрация push_heap и peek_heap === */
static void demo_push_and_peek(void) {
    printf("\n=== Демонстрация: добавление элементов и просмотр вершины ===\n");
    Heap h = create_heap(2, int_copy, int_destroy, int_compare);
    int values[] = {7, 3, 9, 1, 5};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        printf("Добавляем элемент %d...\n", values[i]);
        push_heap(&h, values[i]);
        print_heap(&h, "Куча после вставки");
        printf("Минимальный элемент сейчас: %d\n", peek_heap(&h));
    }
    delete_heap(&h);
}

/* === Демонстрация pop_heap === */
static void demo_pop(void) {
    printf("\n=== Демонстрация: удаление элементов (pop_heap) ===\n");
    int arr[] = {6, 2, 8, 1, 4, 7, 3};
    Heap h = build_heap(arr, sizeof(arr) / sizeof(arr[0]),
                        int_copy, int_destroy, int_compare);
    print_heap(&h, "Построенная куча");
    printf("Извлекаем элементы в порядке возрастания:\n");
    while (!is_empty_heap(&h)) {
        int x = pop_heap(&h);
        printf("%d\n", x);
        print_heap(&h, "Куча после извлечения");
    }
    printf("\n");
    delete_heap(&h);
}

/* === Демонстрация build_heap === */
static void demo_build(void) {
    printf("\n=== Демонстрация: построение кучи из массива ===\n");
    int arr[] = {10, 3, 5, 7, 2, 11, 8, 4};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    Heap h = build_heap(arr, sizeof(arr) / sizeof(arr[0]),
                        int_copy, int_destroy, int_compare);
    print_heap(&h, "После build_heap");
    delete_heap(&h);
}

/* === Демонстрация size_heap === */
static void demo_size(void) {
    printf("\n=== Демонстрация: размер кучи ===\n");
    Heap h = create_heap(1, int_copy, int_destroy, int_compare);
    printf("Текущий размер: %zu\n", size_heap(&h));
    for (int i = 0; i < 5; i++) {
        push_heap(&h, 10 - i);
        printf("После добавления %d размер = %zu\n", 10 - i, size_heap(&h));
    }
    delete_heap(&h);
}

/* === Демонстрация is_equal_heap === */
static void demo_equal(void) {
    printf("\n=== Демонстрация: сравнение куч ===\n");
    int a[] = {5, 1, 9, 2};
    int b[] = {5, 1, 9, 2};
    int c[] = {5, 1, 9, 3};

    Heap h1 = build_heap(a, 4, int_copy, int_destroy, int_compare);
    Heap h2 = build_heap(b, 4, int_copy, int_destroy, int_compare);
    Heap h3 = build_heap(c, 4, int_copy, int_destroy, int_compare);

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
    Heap h = create_heap(3, int_copy, int_destroy, int_compare);
    push_heap(&h, 42);
    push_heap(&h, 7);
    print_heap(&h, "Перед удалением");
    delete_heap(&h);
    printf("После delete_heap: размер = %zu, вместимость = %zu\n",
           h.size, h.capacity);
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
