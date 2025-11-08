#include "../include/demonstration.h"
#include "../include/core.h"
#include <stdio.h>
#include <limits.h>

void demonstrate() {
     const char *tests[] = {
        "", 
        "()", "[]", "{}", "<>",
        "()[]{}", 
        "([{}])", 
        "[({(<()>)}[])]",
        "(((((((((())))))))))",

        "([)]",
        "[(])",
        "(]",
        "(()",
        "())",
        "({[<]})",
        "<(>)",
        "{<[()]>",
        "no closing bracket {",
        "extra closing ) right here",
        "mismatch <]>",

        "text (a + b) [c - {d * (e + f)}]",
        "a(b[c]{d<e>})f",
        "a(b[c]{d<e>)})f",
        "function(x[y{z<w>}])",
        "if ((x[0] < y[1]) && (z > w)) { return; }",

        "no brackets here at all",
        "12345 +-*/ abc",
        "привет, мир!",

        "<html><body>([{}])</body></html>",
        "<div><span></div></span>",
        "<<nested>><<tags>>",
        "<<nested><tags>>",

        "print(\"(text)\")",
        "print('[{<()[]>}]')",
        "\"string with ) inside\" (true)",

        "(((((((((((((((((((((())))))))))))))))))))))",
        "(((((((((((((((((((((()))))))))))))))))))))))",
        "[][][][][][][][][][][][][][][][][][][][]",
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[",

        "{<[(a+b)*(c+d)] + [(x/y)-{z<w>}]} + (p<q>[r{s<t>u}])>",

        "{<[(])>}",
        "{<([)]>}",
        "[({(<)>})]",
        "([{<abc123>}])",
        "([{<abc123>})]",

        "<", ">", "[", "]", "{", "}", "(", ")",
        "<><><><><>",
        "<<<>>>",
        "<<><>>",
        NULL
    };

    puts("Тесты:");
    for (int i = 0; tests[i]; ++i) {
        int ok = check_brackets(tests[i]);
        printf("%2d. %s -> %s\n", i + 1, tests[i], ok ? "OK" : "NO");
    }
}