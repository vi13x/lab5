#include "function.h"
int initStack(Stack *stack, int max_size) {
    if (max_size <= 0 || max_size > MAX_STACK_SIZE) {
        printf("Ошибка: размер стека должен быть от 1 до %d\n", MAX_STACK_SIZE);
        return 0;
    }
    stack->data = (int*) malloc(sizeof(int) * max_size);
    if (!stack->data) {
        printf("Ошибка выделения памяти\n");
        return 0;
    }
    stack->top = -1;
    stack->max_size = max_size;
    return 1;
}

void freeStack(Stack *stack) {
    if (stack->data) {
        free(stack->data);
        stack->data = NULL;
    }
    stack->top = -1;
    stack->max_size = 0;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == stack->max_size - 1;
}

int push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Стек переполнен\n");
        return 0;
    }
    stack->data[++stack->top] = value;
    return 1;
}

int pop(Stack *stack, int *value) {
    if (isEmpty(stack)) {
        return 0;
    }
    *value = stack->data[stack->top--];
    return 1;
}

void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("стек пуст:\n");
        printf("|     |\n");
        printf("|_____|\n");
        return;
    }
    int maxWidth = 5;
    printf("Содержимое стека:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("| %*d |\n", maxWidth, stack->data[i]);
    }
    printf("|");
    for (int i = 0; i < maxWidth + 2; i++) printf("_");
    printf("|\n");
}

int inputInt(const char *prompt, int *value, int min, int max) {
    char buffer[100];
    int n;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            continue;
        }
        char extra;
        if (sscanf(buffer, "%d %c", &n, &extra) != 1) {
            printf("Ошибка: введите целое число.\n");
            continue;
        }
        if (n < min || n > max) {
            printf("Ошибка: число должно быть от %d до %d.\n", min, max);
            continue;
        }
        *value = n;
        return 1;
    }
}

void minStackel() {
    CLEAR_SCREEN();
    printf("Задание 1: Найти минимальный нечетный элемент стека.\n");
    int max_size;
    if (!inputInt("Введите максимальный размер стека (1-1000): ", &max_size, 1, MAX_STACK_SIZE)) {
        return;
    }
    Stack stack;
    if (!initStack(&stack, max_size)) return;
    printf("Введите элементы стека (целые числа). Для окончания ввода введите 0.\n");
    while (!isFull(&stack)) {
        char buffer[100];
        printf("Введите элемент #%d: ", stack.top + 2);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода.\n");
            continue;
        }
        int val;
        char extra;
        if (sscanf(buffer, "%d %c", &val, &extra) != 1) {
            printf("Ошибка: введите целое число или 0 для выхода.\n");
            continue;
        }
        if (val == 0) {
            break;
        }
        push(&stack, val);
    }
    printStack(&stack);
    int min_odd_found = 0;
    int min_odd = 0;
    for (int i = 0; i <= stack.top; i++) {
        if (stack.data[i] % 2 != 0) {
            if (!min_odd_found || stack.data[i] < min_odd) {
                min_odd = stack.data[i];
                min_odd_found = 1;
            }
        }
    }
    if (min_odd_found) {
        printf("Минимальный нечетный элемент стека: %d\n", min_odd);
    } else {
        printf("В стеке нет нечетных элементов.\n");
    }
    freeStack(&stack);
}



void combinationStack() {
    CLEAR_SCREEN();
    printf("Задание 2: Создать два стека и сформировать третий по возрастанию.\n");
    int max_size1, max_size2;
    if (!inputInt("Введите максимальный размер первого стека (1-1000): ", &max_size1, 1, MAX_STACK_SIZE)) return;
    if (!inputInt("Введите максимальный размер второго стека (1-1000): ", &max_size2, 1, MAX_STACK_SIZE)) return;
    Stack stack1, stack2;
    if (!initStack(&stack1, max_size1)) return;
    if (!initStack(&stack2, max_size2)) {
        freeStack(&stack1);
        return;
    }
    printf("Введите элементы первого стека по убыванию (каждый следующий элемент <= предыдущего). Для окончания введите 0.\n");
    while (!isFull(&stack1)) {
        char buffer[100];
        printf("Введите элемент #%d: ", stack1.top + 2);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода.\n");
            continue;
        }
        int val;
        char extra;
        if (sscanf(buffer, "%d %c", &val, &extra) != 1) {
            printf("Ошибка: введите целое число или 0 для выхода.\n");
            continue;
        }
        if (val == 0) break;
        if (!isEmpty(&stack1) && val > stack1.data[stack1.top]) {
            printf("Ошибка: элемент должен быть <= предыдущему (%d).\n", stack1.data[stack1.top]);
            continue;
        }
        push(&stack1, val);
    }
    printf("Введите элементы второго стека по возрастанию (каждый следующий элемент >= предыдущего). Для окончания введите 0.\n");
    while (!isFull(&stack2)) {
        char buffer[100];
        printf("Введите элемент #%d: ", stack2.top + 2);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода.\n");
            continue;
        }
        int val;
        char extra;
        if (sscanf(buffer, "%d %c", &val, &extra) != 1) {
            printf("Ошибка: введите целое число или 0 для выхода.\n");
            continue;
        }
        if (val == 0) break;
        if (!isEmpty(&stack2) && val < stack2.data[stack2.top]) {
            printf("Ошибка: элемент должен быть >= предыдущему (%d).\n", stack2.data[stack2.top]);
            continue;
        }
        push(&stack2, val);
    }
    printf("\nПервый стек (по убыванию):\n");
    printStack(&stack1);
    printf("\nВторой стек (по возрастанию):\n");
    printStack(&stack2);
    Stack stack3;
    int max_size3 = stack1.top + 1 + stack2.top + 1;
    if (!initStack(&stack3, max_size3)) {
        freeStack(&stack1);
        freeStack(&stack2);
        return;
    }
    mergeStacks(&stack1, &stack2, &stack3);
    printf("\nТретий стек (по возрастанию):\n");
    printStack(&stack3);
    freeStack(&stack1);
    freeStack(&stack2);
    freeStack(&stack3);
}

void mergeStacks(Stack *stack1, Stack *stack2, Stack *stack3) {
    Stack copy1, copy2;
    initStack(&copy1, stack1->max_size);
    initStack(&copy2, stack2->max_size);
    for (int i = 0; i <= stack1->top; i++) {
        push(&copy1, stack1->data[i]);
    }
    for (int i = 0; i <= stack2->top; i++) {
        push(&copy2, stack2->data[i]);
    }
    int totalSize = copy1.top + 1 + copy2.top + 1;
    int *buffer = (int*)malloc(sizeof(int) * totalSize);
    int index = 0;
    int value;
    while (pop(&copy1, &value)) buffer[index++] = value;
    while (pop(&copy2, &value)) buffer[index++] = value;
    while (index > 0) {
        int minIndex = 0;
        for (int i = 1; i < index; i++) {
            if (buffer[i] < buffer[minIndex]) {
                minIndex = i;
            }
        }
        push(stack3, buffer[minIndex]);
        for (int i = minIndex; i < index - 1; i++) {
            buffer[i] = buffer[i + 1];
        }
        index--;
    }
    free(buffer);
    freeStack(&copy1);
    freeStack(&copy2);
}
