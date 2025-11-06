#include "../include/vector.h"
#include <stdio.h>

DEFINE_VECTOR(double)

/* === Прототипы тестов === */
void test_create_and_push_double();
void test_get_and_delete_double();
void test_copy_and_compare_double();
void test_copy_vector_new_double();
void test_erase_and_delete_double();

/* === Главная функция === */
int main(void) {
    printf("=== Демонстрация всех функций вектора<double> ===\n\n");

    test_create_and_push_double();
    test_get_and_delete_double();
    test_copy_and_compare_double();
    test_copy_vector_new_double();
    test_erase_and_delete_double();

    return 0;
}

/* === 1. Создание и добавление элементов === */
void test_create_and_push_double() {
    printf("[TEST 1] Создание и добавление элементов\n");

    Vector v = create_vector(2, NULL, NULL);
    printf("Создан вектор: capacity=%zu, size=%zu\n", v.capacity, v.size);

    push_back_vector(&v, 1.1);
    push_back_vector(&v, 2.2);
    push_back_vector(&v, 3.3);
    push_back_vector(&v, 4.4);

    printf("После добавлений: size=%zu, capacity=%zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %.2f\n", i, get_at_vector(&v, i));
    }

    delete_vector(&v);
    printf("Завершено\n\n");
}

/* === 2. Получение и удаление по индексу === */
void test_get_and_delete_double() {
    printf("[TEST 2] Получение и удаление элементов\n");

    Vector v = create_vector(0, NULL, NULL);
    for (int i = 1; i <= 5; i++) push_back_vector(&v, i * 1.5);

    printf("Исходный вектор: ");
    for (size_t i = 0; i < v.size; i++) printf("%.2f ", get_at_vector(&v, i));
    printf("\n");

    printf("Элемент с индексом 2: %.2f\n", get_at_vector(&v, 2));
    printf("Элемент с несуществующим индексом (99): %.2f\n", get_at_vector(&v, 99));

    printf("Удаляем элемент с индексом 1...\n");
    delete_at_vector(&v, 1);

    printf("После удаления: ");
    for (size_t i = 0; i < v.size; i++) printf("%.2f ", get_at_vector(&v, i));
    printf("\n");

    delete_vector(&v);
    printf("Завершено\n\n");
}

/* === 3. Копирование и сравнение векторов === */
void test_copy_and_compare_double() {
    printf("[TEST 3] Копирование и сравнение векторов\n");

    Vector v1 = create_vector(0, NULL, NULL);
    push_back_vector(&v1, 10.5);
    push_back_vector(&v1, 20.25);
    push_back_vector(&v1, 30.75);

    Vector v2 = create_vector(0, NULL, NULL);
    copy_vector(&v2, &v1);

    printf("v1: ");
    for (size_t i = 0; i < v1.size; i++) printf("%.2f ", get_at_vector(&v1, i));
    printf("\nv2: ");
    for (size_t i = 0; i < v2.size; i++) printf("%.2f ", get_at_vector(&v2, i));
    printf("\n");

    printf("Равны ли v1 и v2? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    push_back_vector(&v2, 999.99);
    printf("Добавили 999.99 в v2.\n");
    printf("Теперь равны? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    delete_vector(&v1);
    delete_vector(&v2);
    printf("Завершено\n\n");
}

/* === 4. Копирование с созданием нового вектора === */
void test_copy_vector_new_double() {
    printf("[TEST 4] Копирование с созданием нового вектора\n");

    Vector v = create_vector(0, NULL, NULL);
    for (int i = 1; i <= 4; i++) push_back_vector(&v, i * 2.5);
    printf("Создан новый вектор v:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %.2f\n", i, get_at_vector(&v, i));
    }

    Vector *v_copy = copy_vector_new(&v);
    printf("Создан новый вектор v_copy:\n");
    for (size_t i = 0; i < v_copy->size; i++) {
        printf("  v_copy[%zu] = %.2f\n", i, get_at_vector(v_copy, i));
    }

    delete_vector(&v);
    delete_vector(v_copy);
    free(v_copy);

    printf("Завершено\n\n");
}

/* === 5. Очистка и удаление === */
void test_erase_and_delete_double() {
    printf("[TEST 5] Очистка и удаление\n");

    Vector v = create_vector(0, NULL, NULL);
    push_back_vector(&v, 3.14);
    push_back_vector(&v, 2.71);
    push_back_vector(&v, 1.41);

    printf("Перед очисткой: size=%zu, capacity=%zu\n", v.size, v.capacity);
    erase_vector(&v);
    printf("После erase_vector: size=%zu, capacity=%zu\n", v.size, v.capacity);

    delete_vector(&v);
    printf("Завершено\n\n");
}
