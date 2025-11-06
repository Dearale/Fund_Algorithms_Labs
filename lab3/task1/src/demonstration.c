#include "../include/demonstration.h"
#include "../include/core.h"
#include <stdio.h>
#include <limits.h>

void demonstrate() {
    char res[MAX_NUM_LEN + 1];
    
    int test_numbers[] = {0, 1, -1, 15, -15, 16, -16,
         255, -255, 1024, -1024, 12345, -12345, INT_MAX, INT_MIN};
    int r_values[] = {1, 2, 3, 4, 5};
    
    printf("Тесты:\n\n");
    
    for (size_t i = 0; i < sizeof(test_numbers) / sizeof(test_numbers[0]); i++) {
        printf("Число %d:\n", test_numbers[i]);
        
        for (size_t j = 0; j < sizeof(r_values) / sizeof(r_values[0]); j++) {
            convertTo2Base(test_numbers[i], r_values[j], res);
            printf("  Основание 2^%d (%d): %s\n", 
                   r_values[j], 1 << r_values[j], res);
        }
        printf("\n");
    }

}