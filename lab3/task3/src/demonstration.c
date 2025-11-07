#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/liver.h"
#include "../include/liver_ops.h"
#include "../include/modlog.h"

static void read_line(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t L = strlen(buf);
    while (L && (buf[L - 1] == '\n'))
        buf[--L] = '\0';
}
static size_t read_size_t_prompt(const char *prompt) {
    char s[256];
    size_t v = 0;
    do {
        printf("%s", prompt);
        read_line(s, sizeof(s));
        sscanf(s, "%zu", &v);
        if (v == 0) {
            puts("Введен некорректный id");
        } else {
            break;
        }
    } while (true);
    return v;
}
static double read_double_prompt(const char *prompt, bool is_valid_if_empty, bool *is_empty) {
    char s[256];
    double v = 0.0;
    printf("%s", prompt);
    read_line(s, sizeof(s));
    if (s[0] == '\0' && is_valid_if_empty) {
        if (is_empty) *is_empty = true;
        return v;
    }
    sscanf(s, "%lf", &v);
    return v;
}
static int read_birthdate_prompt(BirthDate *d, bool is_valid_if_empty) {
    char s[256];
    int dd = 0, mm = 0, yy = 0;
    printf("Дата рождения (DD.MM.YYYY или DD-MM-YYYY или DD MM YYYY): ");
    read_line(s, sizeof(s));
    if (s[0] == '\0' && is_valid_if_empty)
    {
        d->day = 0;
        d->month = 0;
        d->year = 0;
        return 1;
    }

    if (sscanf(s, "%d.%d.%d", &dd, &mm, &yy) == 3 ||
        sscanf(s, "%d-%d-%d", &dd, &mm, &yy) == 3 ||
        sscanf(s, "%d %d %d", &dd, &mm, &yy) == 3) {
        d->day = dd;
        d->month = mm;
        d->year = yy;
        if (is_valid_birthdate(*d))
            return 1;
    }
    puts("Некорректная дата.");
    return 0;
}
static void fill_liver_interactive(Liver *lv, bool keep_id) {
    char s[256];
    if (!keep_id)  {

        lv->id = read_size_t_prompt("id: ");
    }
    do {
        printf("Фамилия (латиница): ");
        read_line(lv->last_name, MAX_STR_LEN);
        if (!is_correct_first_or_last_name(lv->last_name)) {
            puts("Некорректная фамилия.");
        } else {
            break;
        }
    } while (true);

    do {
        printf("Имя (латиница): ");
        read_line(lv->first_name, MAX_STR_LEN);
        if (!is_correct_first_or_last_name(lv->first_name)) {
            puts("Некорректное имя.");
        } else {
            break;
        }
    } while (true);
    
    do {
        printf("Отчество (может быть пустым): ");
        read_line(lv->second_name, MAX_STR_LEN);
        if (!is_latin(lv->second_name)) {
            puts("Некорректное отчество.");
        } else {
            break;
        }
    } while (true);

    BirthDate d;
    while (!read_birthdate_prompt(&d, false)) { }

    lv->birthDate = d;
    do {
        printf("Пол (M/W): ");
        read_line(s, sizeof(s));
        if (!(s[0] == 'M' || s[0] == 'W') || s[1] != '\0') {
            puts("Некорректный пол");
        } else {
            break;
        }
    } while (true);
    lv->gender = (char)toupper((unsigned char)(s[0] ? s[0] : 'M'));

    do {
        lv->income = read_double_prompt("Доход: ", false, NULL);
        if (lv->income < 0) {
            puts("Доход должен быть неотрицателен.");
        } else {
            break;
        }
    } while (true);
}

static void fill_liver_interactive_for_update(Liver *lv) {
    char s[256];
    do {
        printf("Фамилия (латиница): ");
        read_line(lv->last_name, MAX_STR_LEN);
        if (!is_latin(lv->last_name)) {
            puts("Некорректная фамилия.");
        } else {
            break;
        }
    } while (true);

    do {
        printf("Имя (латиница): ");
        read_line(lv->first_name, MAX_STR_LEN);
        if (!is_latin(lv->first_name)) {
            puts("Некорректное имя.");
        } else {
            break;
        }
    } while (true);
    
    do {
        printf("Отчество ('-' чтобы сделать пустым): ");
        read_line(lv->second_name, MAX_STR_LEN);
        if (!(lv->second_name[0] == '-' && lv->second_name[1] == '\0') && !is_latin(lv->second_name)) {
            puts("Некорректное отчество.");
        } else {
            break;
        }
    } while (true);

    BirthDate d;
    while (!read_birthdate_prompt(&d, true)) { }

    lv->birthDate = d;
    do {
        printf("Пол (M/W): ");
        read_line(s, sizeof(s));
        if (s[0] != '\0' && (!(s[0] == 'M' || s[0] == 'W') || s[1] != '\0')) {
            puts("Некорректный пол");
        } else {
            break;
        }
    } while (true);
    lv->gender = (char)toupper((unsigned char)(s[0] ? s[0] : 'M'));

    do {
        bool is_empty = false;
        lv->income = read_double_prompt("Доход: ", true, &is_empty);
        if (is_empty) {
            lv->income = -1;
            break;
        }
        if (lv->income < 0) {
            puts("Доход должен быть неотрицателен.");
        } else {
            break;
        }
    } while (true);
}

static void print_list(const LinkedList *list) {
    printf("Всего записей: %zu\n", list->size);
    printf("-------------------------------------------------------------------"
           "-------------------\n");
    printf(
        "  id    LastName   FirstName  SecondName   BirthDate  G   Income\n");
    printf("-------------------------------------------------------------------"
           "-------------------\n");
    for (Node *n = list->head; n; n = n->next) {
        const Liver *lv = n->data;
        printf("%5zu  %-10s %-10s %-12s %02d.%02d.%04d  %c  %8.2f\n", lv->id,
               lv->last_name, lv->first_name,
               lv->second_name[0] ? lv->second_name : "-", lv->birthDate.day,
               lv->birthDate.month, lv->birthDate.year, lv->gender, lv->income);
    }
    printf("-------------------------------------------------------------------"
           "-------------------\n");
}

typedef struct {
    LinkedList list;
    ModLog log;
    bool keep_sorted_by_age;
} AppState;

static void act_print(AppState *app) { print_list(&app->list); }
static void act_search(AppState *app) {
    LiverQuery q = {0};
    char s[256];
    printf("Фильтры (Enter чтобы пропустить)\n");
    printf("id: ");
    read_line(s, sizeof(s));
    if (s[0]) {
        q.set_id = 1;
        sscanf(s, "%zu", &q.id);
    }
    printf("Фамилия: ");
    read_line(q.last_name, MAX_STR_LEN);
    if (q.last_name[0])
        q.set_last = 1;
    printf("Имя: ");
    read_line(q.first_name, MAX_STR_LEN);
    if (q.first_name[0])
        q.set_first = 1;
    printf("Отчество (\"-\" для пустого): ");
    read_line(q.second_name, MAX_STR_LEN);
    if (q.second_name[0]) {
        q.set_second = 1;
        if (strcmp(q.second_name, "-") == 0)
            q.second_name[0] = '\0';
    }
    printf("Пол (M/W): ");
    read_line(s, sizeof(s));
    if (s[0]) {
        q.set_gender = 1;
        q.gender = (char)toupper((unsigned char)s[0]);
    }
    printf("Дата от (DD.MM.YYYY/пусто): ");
    read_line(s, sizeof(s));
    if (s[0]) {
        int d, m, y;
        if (sscanf(s, "%d.%d.%d", &d, &m, &y) == 3) {
            q.set_birth_from = 1;
            q.birth_from = (BirthDate){d, m, y};
        }
    }
    printf("Дата до (DD.MM.YYYY/пусто): ");
    read_line(s, sizeof(s));
    if (s[0]) {
        int d, m, y;
        if (sscanf(s, "%d.%d.%d", &d, &m, &y) == 3) {
            q.set_birth_to = 1;
            q.birth_to = (BirthDate){d, m, y};
        }
    }
    printf("Доход >= : ");
    read_line(s, sizeof(s));
    if (s[0]) {
        q.set_income_min = 1;
        q.income_min = strtod(s, NULL);
    }
    printf("Доход <= : ");
    read_line(s, sizeof(s));
    if (s[0]) {
        q.set_income_max = 1;
        q.income_max = strtod(s, NULL);
    }

    size_t idxs[1024];
    size_t total = find_all_indices(&app->list, &q, idxs, 1024);
    printf("\n----Найдено: %zu\n", total);
    for (size_t i = 0; i < total && i < 1024; ++i) {
        Liver lv = get_at_list(&app->list, idxs[i]);
        printf("[%zu] %zu %s %s %s %02d.%02d.%04d %c %.2f\n", idxs[i], lv.id,
               lv.last_name, lv.first_name,
               lv.second_name[0] ? lv.second_name : "-", lv.birthDate.day,
               lv.birthDate.month, lv.birthDate.year, lv.gender, lv.income);
    }
}
static void act_add(AppState *app) {
    Liver v = (Liver){0};
    fill_liver_interactive(&v, /*keep_id=*/false);
    bool res = add_resident(&app->list, &v, app->keep_sorted_by_age, &app->log);
    if (res)
        puts("Добавлено.");
    else
        puts("\n-X- Житель с таким id уже есть");
}
static void act_remove(AppState *app) {
    size_t id = read_size_t_prompt("Удалить id: ");
    if (remove_by_id(&app->list, id, app->keep_sorted_by_age, &app->log))
        puts("Удалено.");
    else
        puts("Не найдено.");
}
static void act_update(AppState *app) {
    size_t id = read_size_t_prompt("Изменить запись с id: ");
    size_t idx;
    if (!find_index_by_id(&app->list, id, &idx)) {
        puts("Не найдено с этим id");
        return;
    }
    Liver v = (Liver){0};
    fill_liver_interactive_for_update(&v);

    Liver cur = get_at_list(&app->list, idx);
    v.id = cur.id;
    if (v.birthDate.day == 0) v.birthDate = cur.birthDate;
    if (v.first_name[0] == '\0') strncpy(v.first_name, cur.first_name, MAX_STR_LEN - 1);
    if (v.last_name[0] == '\0') strncpy(v.last_name, cur.last_name, MAX_STR_LEN - 1);
    if (v.second_name[0] == '\0') strncpy(v.second_name, cur.second_name, MAX_STR_LEN - 1);
    if (v.gender == '\0') v.gender = cur.gender;
    if (v.income < 0) v.income = cur.income;

    if (update_by_id(&app->list, id, &v, app->keep_sorted_by_age, &app->log))
        puts("Изменено.");
    else
        puts("Не найдено.");
}
static void act_save(AppState *app, char *outPath) {
    int rc = save_residents_to_file(outPath, &app->list);
    if (rc)
        fprintf(stderr, "Ошибка сохранения (%d)\n", rc);
}
static void act_undo(AppState *app) {
    size_t undone = modlog_undo_last_half(&app->log, &app->list);
    printf("Откатили модификаций: %zu\n", undone);
}
static void act_toggle_sort(AppState *app) {
    app->keep_sorted_by_age = !app->keep_sorted_by_age;
    sort_list_by_age(&(app->list));
    printf("Сортировка по возрасту теперь: %s\n",
           app->keep_sorted_by_age ? "ON" : "OFF");
}

static void print_menu(bool keep_sorted) {
    puts("\n=== Меню ===");
    printf("Сортировка по возрасту: %s\n", keep_sorted ? "ON" : "OFF");
    puts("1. Вывести всех");
    puts("2. Поиск");
    puts("3. Добавить");
    puts("4. Удалить по id");
    puts("5. Изменить по id");
    puts("6. Сохранить в файл");
    puts("7. Undo (последние N/2 модификаций)");
    puts("8. Переключить сортировку по возрасту");
    puts("0. Выход");
    printf("Выбор: ");
}

int demonstrate(LinkedList *list, char *outPath) {
    AppState app;
    app.list = *list;
    modlog_init(&app.log);

    char s[32];
    app.keep_sorted_by_age = true;

    for (;;) {
        print_menu(app.keep_sorted_by_age);
        read_line(s, sizeof(s));
        int choice = (int)strtol(s, NULL, 10);
        switch (choice) {
        case 1:
            act_print(&app);
            break;
        case 2:
            act_search(&app);
            break;
        case 3:
            act_add(&app);
            break;
        case 4:
            act_remove(&app);
            break;
        case 5:
            act_update(&app);
            break;
        case 6:
            act_save(&app, outPath);
            break;
        case 7:
            act_undo(&app);
            break;
        case 8:
            act_toggle_sort(&app);
            break;
        case 0:
            modlog_free(&app.log);
            delete_list(&app.list);
            puts("Bye!");
            return 0;
        default:
            puts("Неверный пункт.");
        }
    }
}
