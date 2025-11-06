#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DEFINE_VECTOR(char*)

/* === Пользовательские функции для работы со строками === */

// Копирование строки (для CopyVoidPtr)
char* copy_string(char* src) {
    if (!src) return NULL;
    char* copy = strdup(src);
    if (!copy) {
        fprintf(stderr, "Ошибка: не удалось скопировать строку.\n");
        exit(EXIT_FAILURE);
    }
    return copy;
}

// Удаление строки (для DeleteVoidPtr)
void delete_string(char* str) {
    free(str);
}

/* === Прототипы тестов === */
void test_create_and_push_string();
void test_get_and_delete_string();
void test_copy_and_compare_string();
void test_copy_vector_new_string();
void test_erase_and_delete_string();

/* === Главная функция === */
int main(void) {
    printf("=== Демонстрация всех функций вектора<char*> ===\n\n");

    test_create_and_push_string();
    test_get_and_delete_string();
    test_copy_and_compare_string();
    test_copy_vector_new_string();
    test_erase_and_delete_string();

    return 0;
}

/* === 1. Создание и добавление элементов === */
void test_create_and_push_string() {
    printf("[TEST 1] Создание и добавление строк\n");

    Vector v = create_vector(2, copy_string, delete_string);
    printf("Создан вектор: capacity=%zu, size=%zu\n", v.capacity, v.size);

    push_back_vector(&v, "Привет");
    push_back_vector(&v, "мир");
    push_back_vector(&v, "из");
    push_back_vector(&v, "вектора");

    printf("После добавлений: size=%zu, capacity=%zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = \"%s\"\n", i, get_at_vector(&v, i));
    }

    delete_vector(&v);
    printf("Завершено\n\n");
}

/* === 2. Получение и удаление по индексу === */
void test_get_and_delete_string() {
    printf("[TEST 2] Получение и удаление строк\n");

    Vector v = create_vector(0, copy_string, delete_string);
    push_back_vector(&v, "Один");
    push_back_vector(&v, "Два");
    push_back_vector(&v, "Три");
    push_back_vector(&v, "Четыре");

    printf("Исходный вектор:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = \"%s\"\n", i, get_at_vector(&v, i));
    }

    printf("Удаляем элемент с индексом 1...\n");
    delete_at_vector(&v, 1);

    printf("После удаления:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = \"%s\"\n", i, get_at_vector(&v, i));
    }

    delete_vector(&v);
    printf("Завершено\n\n");
}

/* === 3. Копирование и сравнение векторов === */
void test_copy_and_compare_string() {
    printf("[TEST 3] Копирование и сравнение строковых векторов\n");

    Vector v1 = create_vector(0, copy_string, delete_string);
    push_back_vector(&v1, "apple");
    push_back_vector(&v1, "banana");
    push_back_vector(&v1, "cherry");

    Vector v2 = create_vector(0, copy_string, delete_string);
    copy_vector(&v2, &v1);

    printf("v1:\n");
    for (size_t i = 0; i < v1.size; i++) printf("  %s\n", get_at_vector(&v1, i));
    printf("v2:\n");
    for (size_t i = 0; i < v2.size; i++) printf("  %s\n", get_at_vector(&v2, i));

    printf("Равны ли v1 и v2? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    push_back_vector(&v2, "date");
    printf("Добавили новый элемент в v2.\n");
    printf("Теперь равны? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    delete_vector(&v1);
    delete_vector(&v2);
    printf("Завершено\n\n");
}

/* === 4. Копирование с созданием нового вектора === */
void test_copy_vector_new_string() {
    printf("[TEST 4] Копирование с созданием нового строкового вектора\n");

    Vector v = create_vector(0, copy_string, delete_string);
    push_back_vector(&v, "one");
    push_back_vector(&v, "two");
    push_back_vector(&v, "three");
    printf("Создан новый вектор v:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = \"%s\"\n", i, get_at_vector(&v, i));
    }

    Vector *v_copy = copy_vector_new(&v);
    printf("Создан новый вектор v_copy:\n");
    for (size_t i = 0; i < v_copy->size; i++) {
        printf("  v_copy[%zu] = \"%s\"\n", i, get_at_vector(v_copy, i));
    }

    delete_vector(&v);
    delete_vector(v_copy);
    free(v_copy);

    printf("Завершено\n\n");
}

/* === 5. Очистка и удаление === */
void test_erase_and_delete_string() {
    printf("[TEST 5] Очистка и удаление строкового вектора\n");

    Vector v = create_vector(0, copy_string, delete_string);
    push_back_vector(&v, "alpha");
    push_back_vector(&v, "beta");
    push_back_vector(&v, "gamma");

    printf("Перед очисткой: size=%zu, capacity=%zu\n", v.size, v.capacity);
    erase_vector(&v);
    printf("После erase_vector: size=%zu, capacity=%zu\n", v.size, v.capacity);

    delete_vector(&v);
    printf("Завершено\n\n");
}
