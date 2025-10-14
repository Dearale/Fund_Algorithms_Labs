#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/student.h"
#include "../include/studentAdditional.h"
#include "../include/studentCompare.h"
#include "../include/studentFind.h"
#include "../include/studentPrint.h"
#include "../include/statusManager.h"

void printUsage() {
    printf("Использование: ./main.out <входной файл> <выходной файл>.\n");
}

void printChoices() {
    printf("1. Поиск по ID\n");
    printf("2. Поиск по фамилии\n");
    printf("3. Поиск по имени\n");
    printf("4. Поиск по группе\n");
    printf("5. Сортировка по ID\n");
    printf("6. Сортировка по фамилии\n");
    printf("7. Сортировка по имени\n");
    printf("8. Сортировка по группе\n");
    printf("9. Сохранить студента по ID\n");
    printf("10. Сохранить лучших студентов\n");
    printf("11. Вывести всех студентов\n");
    printf("12. Выход\n");
}

Status handleChoices(Students *students, char *outPath) {
    unsigned int idInput;
    char searchInput[MAX_STRING];
    int choice;
    do {
        printChoices();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Введите ID:\n");
                scanf("%u", &idInput);
                printStudentsWithID(students, idInput);
                break;
            case 2:
                printf("Введите фамилию:\n");
                scanf("%s", searchInput);
                printStudentsWithLastName(students, searchInput);
                break;
            case 3:
                printf("Введите имя:\n");
                scanf("%s", searchInput);
                printStudentsWithFirstName(students, searchInput);
                break;
            case 4:
                printf("Введите группу:\n");
                scanf("%s", searchInput);
                printStudentsWithGroup(students, searchInput);
                break;
            case 5:
                qsort(students->data, students->size, sizeof(Student), cmpId);
                printf("Отсортировано по ID\n");
                break;
            case 6:
                qsort(students->data, students->size, sizeof(Student), cmpLastName);
                printf("Отсортировано по фамилии\n");
                break;
            case 7:
                qsort(students->data, students->size, sizeof(Student), cmpFirstName);
                printf("Отсортировано по имени\n");
                break;
            case 8:
                qsort(students->data, students->size, sizeof(Student), cmpGroup);
                printf("Отсортировано по группе\n");
                break;
            case 9: {
                printf("Введите ID:\n");
                scanf("%u", &idInput);
                Status status = trySaveStudentByID(students, idInput, outPath);
                if (status == OK) {
                    printf("Студент сохранен\n");
                } else if (status == COULDNT_OPEN_FILE) {
                    return status;
                } else {
                    printf("Студент с данным id не найден\n");
                }
                break;
            }
            case 10: {
                Status status = saveBestStudents(students, outPath);
                if (status == COULDNT_OPEN_FILE) {
                    return status;
                }
                printf("Лучшая половина студентов сохранена\n");
                break;
            }
            case 11:
                printAllStudents(students);
                break;
            case 12:
                printf("Выходим\n");
                break;
            default:
                printf("Невалидный выбор\n");
        }
    } while (choice != 12);

    return OK;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printUsage();
        return 1;
    }
    char * inPath = argv[1];
    FILE * fin = fopen(inPath, "r");
    if (!fin) {
        printf("Ошибка: не удалось открыть входной файл.");
        return 1;
    }

    char *outPath = argv[2];
    FILE * fout = fopen(outPath, "w");
    if (!fout) {
        printf("Ошибка: не удалось открыть выходной файл.");
        return 1;
    }
    fclose(fout);

    Students students;
    Status status = readStudents(fin, &students);
    if (status != OK) {
        printStatus(status);
        return 1;
    }
    fclose(fin);

    status = handleChoices(&students, outPath);
    printStatus(status);
    freeStudents(&students);
    return 0;
}