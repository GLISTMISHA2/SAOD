#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Заполнение массива возрастающими числами
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

// Заполнение массива убывающими числами
void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

// Заполнение массива случайными числами
void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // случайные числа от 0 до 99
    }
}

// Подсчет контрольной суммы элементов массива
int CheckSum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Подсчет количества серий в массиве
int RunNumber(int A[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) {
            count++;
        }
    }
    return count;
}

// Вывод элементов массива на экран
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d",&n);
    int A[n];

    // Заполнение массива возрастающими числами
    FillInc(A, n);
    printf("Возрастающий массив: ");
    PrintMas(A, n);
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("Контрольная сумма: %d\n", CheckSum(A, n));

    // Заполнение массива убывающими числами
    FillDec(A, n);
    printf("Убывающий массив: ");
    PrintMas(A, n);
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("Контрольная сумма: %d\n", CheckSum(A, n));

    // Заполнение массива случайными числами
    FillRand(A, n);
    printf("Случайный массив: ");
    PrintMas(A, n);
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("Контрольная сумма: %d\n", CheckSum(A, n));

    // Дополнительное задание: средняя длина серии в случайном массиве
    int totalRuns = RunNumber(A, n);
    float averageRunLength = (float)n / totalRuns;
    printf("Средняя длина серии в случайном массиве: %.2f\n", averageRunLength);

    return 0;
}