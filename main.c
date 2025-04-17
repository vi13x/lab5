#include "function.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    while (1) {
        printf("\nВыберите задание лабораторной работы №5:\n");
        printf("0 - Завершить программу\n");
        printf("1 - Первое задание (минимальный нечетный элемент стека)\n");
        printf("2 - Второе задание (слияние двух стеков)\n");
        printf("Введите номер задания: ");
        int choice;
        if (!inputInt("", &choice, 0, 2)) continue;
        if (choice == 0) {
            printf("Завершение программы.\n");
            break;
        } else if (choice == 1) {
            minStackel();
        } else if (choice == 2) {
            combinationStack();
        } else {
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}
