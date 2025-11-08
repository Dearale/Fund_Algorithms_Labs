#include "../include/core.h"
#include "../include/linkedList.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

DEFINE_LINKED_LIST(char);

void delete_func(char x) { (void)x; }

char copy_func(char x) { return x; }

int compare_func(char x, char y) { return x - y; }

int get_bracket_type(char bracket) {
    if (bracket == '(' || bracket == ')') return 1;
    if (bracket == '[' || bracket == ']') return 2;
    if (bracket == '{' || bracket == '}') return 3;
    if (bracket == '<' || bracket == '>') return 4;
    return 0;
}

int is_bracket_open(char bracket) {
    if (bracket == '(' || bracket == '[' || bracket == '{' || bracket == '<') {
        return 1;
    }

    if (bracket == ')' || bracket == ']' || bracket == '}' || bracket == '>') {
        return 0;
    }

    return -1;
}

int check_brackets(const char *str) {
    LinkedList stack = create_list(delete_func, copy_func, compare_func, 0);
    const char *p = str;
    while (*p) {
        int type = get_bracket_type(*p);
        if (type == 0) {
            p++;
            continue;
        }

        if (is_bracket_open(*p)) {
            push_stack(&stack, *p);
        } else {
            if (stack.size == 0) {
                delete_list(&stack);
                return 0;
            }
            
            char top = pop_stack(&stack);
            if (get_bracket_type(top) != type) {
                delete_list(&stack);
                return 0;
            }
        }
        p++;
    }

    int res = (stack.size == 0);
    delete_list(&stack);
    return res;
}