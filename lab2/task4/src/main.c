#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "../include/core.h"
#include "../include/demonstration.h"

// Демонстрация использования oversscanf / overfscanf.
// Печатаем входные данные, формат и то, что прочитали.

#define _POSIX_C_SOURCE 200809L
#include <stdarg.h>
#include <string.h>


// Утилита: симпатичный заголовок блока
static void hr(const char *title) {
    printf("\n========================================\n");
    printf("%s\n", title);
    printf("========================================\n");
}

// Печать результата парсинга «чисел»: int/unsigned/две int и т.п.
static void print_ok_count(const char *label, int ok_count) {
    printf("→ Присвоено полей: %d  (%s)\n", ok_count, label);
}

int main(void) {
    demonstrate();
    return 0;

    // ---------- 1) oversscanf: стандартные спецификаторы ----------
    hr("1) oversscanf: базовая проверка стандартных спецификаторов");
    {
        char *in = "42 -17 0x2a 3.14 Hello";
        int d = 0, di = 0;
        unsigned ux = 0;
        float f = 0.f;
        char s[32] = {0};

        const char *fmt_std = "%d %d %x %f %s";
        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt_std);

        int ok = oversscanf(in, fmt_std, &d, &di, &ux, &f, s);
        print_ok_count("стандарт", ok);
        printf("d=%d, di=%d, ux=%u, f=%.2f, s=\"%s\"\n", d, di, ux, f, s);
    }

    // ---------- 2) %Ro — римские цифры ----------
    hr("2) oversscanf: %Ro — римские цифры → int");
    {
        char *in = "MMXXV  iv  XLII  end";
        const char *fmt = "%Ro %Ro %Ro %s";   // читаем 3 римских и «хвост» словом
        int a=0,b=0,c=0;
        char tail[16]={0};

        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt);

        int ok = oversscanf(in, fmt, &a, &b, &c, tail);
        print_ok_count("%Ro", ok);
        printf("a=%d, b=%d, c=%d, tail=\"%s\"\n", a, b, c, tail);
        printf("Ожидаемо: MMXXV=2025, iv=4, XLII=42\n");
    }

    // ---------- 3) %Zr — «цекендорф» (Фибоначчево кодирование) ----------
    hr("3) oversscanf: %Zr — цекендорфово представление → unsigned int");
    {
        // Коэффициенты 0/1 от младших к старшим СЛЕВА→НАПРАВО, затем терминатор '1'.
        // Пример строки ниже — три числа подряд и слово.
        char *in = "1011  00101  11  stop";
        const char *fmt = "%Zr %Zr %Zr %s";

        unsigned u1=0, u2=0, u3=0;
        char tail[16]={0};

        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt);

        int ok = oversscanf(in, fmt, &u1, &u2, &u3, tail);
        print_ok_count("%Zr", ok);
        printf("u1=%u, u2=%u, u3=%u, tail=\"%s\"\n", u1, u2, u3, tail);
        printf("Ожидаемо: 1011=4, 00101=3, 11=1\n");
    }

    // ---------- 4) %Cv — основание задаётся вторым аргументом; буквы нижний регистр ----------
    hr("4) oversscanf: %Cv — система счисления (буквы в НИЖНЕМ регистре) → int");
    {
        char *in  = "ff  1011  -1a  z";
        const char *fmt = "%Cv %Cv %Cv %Cv";

        int v1=0, v2=0, v3=0, v4=0;

        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt);
        printf("Базы:   16, 2, 16, 36\n");

        // %Cv: каждый спецификатор принимает (int*, base)
        int ok = oversscanf(in, fmt,
                            &v1, 16,
                            &v2, 2,
                            &v3, 16,
                            &v4, 36);
        print_ok_count("%Cv", ok);
        printf("v1=%d, v2=%d, v3=%d, v4=%d\n", v1, v2, v3, v4);
        printf("Ожидаемо: ff(16)=255, 1011(2)=11, -1a(16)=-26, z(36)=35\n");
    }

    // ---------- 5) %CV — основание задаётся вторым аргументом; буквы верхний регистр ----------
    hr("5) oversscanf: %CV — система счисления (буквы в ВЕРХНЕМ регистре) → int");
    {
        char *in  = "FF  1A  Z";
        const char *fmt = "%CV %CV %CV";

        int v1=0, v2=0, v3=0;

        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt);
        printf("Базы:   16, 16, 36\n");

        int ok = oversscanf(in, fmt, &v1, 16, &v2, 16, &v3, 36);
        print_ok_count("%CV", ok);
        printf("v1=%d, v2=%d, v3=%d\n", v1, v2, v3);
        printf("Ожидаемо: FF(16)=255, 1A(16)=26, Z(36)=35\n");
    }

    // ---------- 6) Смешанный формат: стандарт + кастом ----------
    hr("6) oversscanf: смешанный формат (стандарт + кастом)");
    {
        char *in  = "ID=42  ROM=XLII  BASE36=Z  tail";
        const char *fmt = "ID=%d  ROM=%Ro  BASE36=%CV  %s";

        int id=0, rom=0, base36=0;
        char tail[16]={0};

        printf("Вход:   \"%s\"\n", in);
        printf("Формат: \"%s\"\n", fmt);

        int ok = oversscanf(in, fmt, &id, &rom, &base36, 36, tail);
        print_ok_count("смешанный", ok);
        printf("id=%d, rom=%d, base36=%d, tail=\"%s\"\n", id, rom, base36, tail);
    }

    // ---------- 7) overfscanf: чтение из файла (те же спеки) ----------
    hr("7) overfscanf: чтение из файла с кастомными флагами");
    {
        const char *payload =
            "MMXXV\n"      // %Ro
            "00101" "1\n"  // %Zr (коэфы + терминатор '1')
            "ff\n"         // %Cv (base 16)
            "Z\n"          // %CV (base 36)
            "the_end\n";   // %s
        const char *path = "demo_input.txt";

        // Пишем входной файл
        FILE *w = fopen(path, "wb");
        if (!w) { perror("fopen(write)"); return 1; }
        fputs(payload, w);
        fclose(w);

        // Читаем
        FILE *r = fopen(path, "rb");
        if (!r) { perror("fopen(read)"); return 1; }

        printf("Содержимое файла \"%s\":\n---\n%s---\n", path, payload);

        int rom=0;
        unsigned zr=0;
        int cv=0, cvU=0;
        char tail[32]={0};

        int ok1 = overfscanf(r, "%Ro", &rom);
        int ok2 = overfscanf(r, "%Zr", &zr);
        int ok3 = overfscanf(r, "%Cv", &cv, 16);
        int ok4 = overfscanf(r, "%CV", &cvU, 36);
        int ok5 = overfscanf(r, "%s", tail);

        fclose(r);

        print_ok_count("%Ro", ok1);
        printf("rom=%d\n", rom);

        print_ok_count("%Zr", ok2);
        printf("zr=%u\n", zr);

        print_ok_count("%Cv", ok3);
        printf("cv(base16)=%d\n", cv);

        print_ok_count("%CV", ok4);
        printf("cvU(base36)=%d\n", cvU);

        print_ok_count("%s", ok5);
        printf("tail=\"%s\"\n", tail);
    }

    return 0;
}