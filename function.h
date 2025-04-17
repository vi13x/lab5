#define CLEAR_SCREEN() system("cls")
#define MAX_STACK_SIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct {
    int *data;
    int top;
    int max_size;
} Stack;
int initStack(Stack *stack, int max_size);
void freeStack(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int push(Stack *stack, int value);
int pop(Stack *stack, int *value);
void printStack(Stack *stack);
int inputInt(const char *prompt, int *value, int min, int max);
void minStackel();
void mergeStacks(Stack *stack1, Stack *stack2, Stack *stack3);
void combinationStack();
void mergeStacks(Stack *stack1, Stack *stack2, Stack *stack3);