#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getPrimeAt(int idx) {
    int cur = 1;
    int curI = 1;
    do {
        cur++;
        int isPrime = 1;
        int sqr = (int)ceil(sqrt(cur));
        for (size_t i = 2; i <= sqr; i++)
        {
            if (cur % i == 0) {
                isPrime = 0;
                break;
            }
        }
        
        if (isPrime)
            curI++;
    } while (idx != curI);
    return cur;
}

int main() {
    const int MAX_TESTS = 1000;
    const int MAX_IDX = 50000;

    printf("Напишите количество номеров и сами номера:\n");
    int t;
    scanf("%d", &t);
    if (t > MAX_TESTS) {
        printf("Количество тестов не должно превышать %d.\n", MAX_TESTS);
        return 1;
    }
    if (t <= 0) {
        printf("Количество тестов должно быть больше нуля");
        return 1;
    }
    int res[t];
    for (size_t i = 0; i < t; i++)
    {
        int idx;
        scanf("%d", &idx);
        if (idx > MAX_IDX || idx <= 0) {
            printf("Максимальный индекс не должен превышать %d.\n", MAX_IDX);
            return 1;
        }

        int prime = getPrimeAt(idx);
        res[i] = prime;
    }
    
    printf("\nРезультат:\n");
    for (size_t i = 0; i < t; i++)
    {
        printf("%d\n", res[i]);
    }
    

    return 0;
}