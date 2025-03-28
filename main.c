#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int max_size;
    printf("Введите максимальный размер стека: ");
    scanf("%d", &max_size);

    int *stack = (int*)malloc(max_size * sizeof(int));
    int top = -1;

    printf("Введите %d целых чисел:\n", max_size);
    for (int i = 0; i < max_size; i++) {
        int value;
        scanf("%d", &value);
        stack[++top] = value;
    }


    int min = stack[0];
    for (int i = 1; i <= top; i++) {
        if (stack[i] < min) {
            min = stack[i];
        }
    }

    printf("Минимальный элемент стека: %d\n", min);

    free(stack);
    return 0;
}
