#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"


/* === Определяем структуру Person === */
typedef struct {
    char* name;
    int age;
} Person;

DEFINE_HEAP(Person)
/* === Колбэки для кучи типа Person === */

// Копирование Person (глубокое — копируем строку имени)
static Person person_copy(Person p) {
    Person new_p;
    new_p.age = p.age;
    if (p.name) {
        size_t len = strlen(p.name);
        new_p.name = (char*)malloc(len + 1);
        if (!new_p.name) {
            fprintf(stderr, "Ошибка: не удалось выделить память для имени.\n");
            abort();
        }
        memcpy(new_p.name, p.name, len + 1);
    } else {
        new_p.name = NULL;
    }
    return new_p;
}

// Уничтожение Person (освобождение имени)
static void person_destroy(Person p) {
    free(p.name);
}

// Сравнение по возрасту (меньший возраст = более высокий приоритет)
static int person_compare(Person a, Person b) {
    if (a.age < b.age) return -1;
    if (a.age > b.age) return 1;
    return 0;
}

/* === Печать содержимого кучи === */
static void print_heap(const Heap *h, const char *title) {
    printf("%s (размер=%zu, вместимость=%zu): [\n", title, h->size, h->capacity);
    for (size_t i = 0; i < h->size; i++) {
        printf("    {имя: \"%s\", возраст: %d}%s\n",
               h->data[i].name,
               h->data[i].age,
               (i + 1 < h->size) ? ", " : "");
    }
    printf("]\n");
}

/* === Демонстрация create_heap и is_empty_heap === */
static void demo_create_and_empty(void) {
    printf("\n=== Демонстрация: создание кучи Person и проверка пустоты ===\n");
    Heap h = create_heap(5, person_copy, person_destroy, person_compare);
    print_heap(&h, "После создания");
    printf("Пуста ли куча? %s\n", is_empty_heap(&h) ? "Да" : "Нет");
    delete_heap(&h);
}

/* === Демонстрация push_heap и peek_heap === */
static void demo_push_and_peek(void) {
    printf("\n=== Демонстрация: добавление людей и просмотр вершины ===\n");
    Heap h = create_heap(2, person_copy, person_destroy, person_compare);

    Person people[] = {
        {"Алексей", 32},
        {"Мария", 25},
        {"Иван", 41},
        {"Ольга", 19},
        {"Никита", 28}
    };

    for (size_t i = 0; i < sizeof(people)/sizeof(people[0]); i++) {
        printf("Добавляем человека: %s (%d лет)\n", people[i].name, people[i].age);
        push_heap(&h, people[i]);
        print_heap(&h, "Текущее состояние кучи");
        Person top = peek_heap(&h);
        printf("Сейчас минимальный (самый молодой): %s (%d лет)\n\n", top.name, top.age);
    }

    delete_heap(&h);
}

/* === Демонстрация pop_heap === */
static void demo_pop(void) {
    printf("\n=== Демонстрация: извлечение людей из кучи ===\n");
    Person people[] = {
        {"Андрей", 40}, {"Сергей", 18}, {"Павел", 29},
        {"Дмитрий", 22}, {"Екатерина", 35}
    };

    Heap h = build_heap(people, sizeof(people)/sizeof(people[0]),
                        person_copy, person_destroy, person_compare);
    print_heap(&h, "Построенная куча");
    printf("\nИзвлекаем людей в порядке возрастания возраста:\n");
    while (!is_empty_heap(&h)) {
        Person p = pop_heap(&h);
        printf("%s (%d лет)\n", p.name, p.age);
        print_heap(&h, "Куча после извлечения");
        person_destroy(p); // освободить имя
        printf("\n");
    }
    delete_heap(&h);
}

/* === Демонстрация build_heap === */
static void demo_build(void) {
    printf("\n=== Демонстрация: построение кучи из массива ===\n");
    Person people[] = {
        {"Владимир", 42}, {"Анна", 20}, {"Егор", 31}, {"Наталья", 27}
    };
    for (size_t i = 0; i < sizeof(people) / sizeof(people[0]); i++) {
        printf("%s (%d лет) ", people[i].name, people[i].age);
    }
    printf("\n");
    Heap h = build_heap(people, sizeof(people)/sizeof(people[0]),
                        person_copy, person_destroy, person_compare);
    print_heap(&h, "После build_heap");
    delete_heap(&h);
}

/* === Демонстрация size_heap === */
static void demo_size(void) {
    printf("\n=== Демонстрация: размер кучи ===\n");
    Heap h = create_heap(1, person_copy, person_destroy, person_compare);
    printf("Текущий размер: %zu\n", size_heap(&h));
    Person people[] = {
        {"Катя", 24}, {"Олег", 27}, {"Таня", 22}
    };
    for (size_t i = 0; i < sizeof(people)/sizeof(people[0]); i++) {
        push_heap(&h, people[i]);
        printf("После добавления %s размер = %zu\n", people[i].name, size_heap(&h));
    }
    delete_heap(&h);
}

/* === Демонстрация is_equal_heap === */
static void demo_equal(void) {
    printf("\n=== Демонстрация: сравнение куч ===\n");
    Person a[] = {{"Аня", 18}, {"Борис", 30}, {"Вика", 25}};
    Person b[] = {{"Аня", 18}, {"Борис", 30}, {"Вика", 25}};
    Person c[] = {{"Аня", 18}, {"Борис", 30}, {"Вика", 26}};

    Heap h1 = build_heap(a, 3, person_copy, person_destroy, person_compare);
    Heap h2 = build_heap(b, 3, person_copy, person_destroy, person_compare);
    Heap h3 = build_heap(c, 3, person_copy, person_destroy, person_compare);

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
    Heap h = create_heap(3, person_copy, person_destroy, person_compare);
    push_heap(&h, (Person){"Илья", 37});
    push_heap(&h, (Person){"Галина", 45});
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
