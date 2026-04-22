#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Узел связного списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура стека
typedef struct {
    Node* top;
} Stack;

// Структура очереди 
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// пустой стек
void initStack(Stack* s) {
    s->top = NULL;
}

// пустая очередь
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Добавляет элемент на вершину стека
void push(Stack* s, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

// Добавляет элемент в конец очереди
void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Заполняет стек числами от 1 до n (возрастание)
void fillStackAscending(Stack* s, int n) {
    for (int i = 1; i <= n; i++) {
        push(s, i);
    }
}

// Заполняет стек числами от n до 1 (убывание)
void fillStackDescending(Stack* s, int n) {
    for (int i = n; i >= 1; i--) {
        push(s, i);
    }
}

// Заполняет стек n случайными числами в заданном диапазоне
void fillStackRandom(Stack* s, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1);
        push(s, num);
    }
}

// Заполняет очередь числами от 1 до n (возрастание)
void fillQueueAscending(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

// Заполняет очередь числами от n до 1 (убывание)
void fillQueueDescending(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}

// Заполняет очередь n случайными числами в заданном диапазоне
void fillQueueRandom(Queue* q, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, num);
    }
}

// Выводит элементы списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Рекурсивно выводит элементы списка в прямом порядке
void printListForwardRecursive(Node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", head->data);
    printListForwardRecursive(head->next);
}

// Рекурсивно выводит элементы списка в обратном порядке
void printListBackwardRecursive(Node* head) {
    if (head == NULL) {
        return;
    }
    printListBackwardRecursive(head->next);
    printf("%d ", head->data);
    if (head->next == NULL) {
        printf("\n");
    }
}

// Вычисляет сумму всех элементов списка
int calculateChecksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Считает количество убывающих серий в списке
int countSeries(Node* head) {
    if (head == NULL) return 0;
    int series = 1;
    Node* current = head;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    return series;
}

// Очищает очередь и освобождает память
void clearQueue(Queue* q) {
    Node* current = q->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

// Очищает стек и освобождает память
void clearStack(Stack* s) {
    Node* current = s->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    s->top = NULL;
}

// Демонстрация работы со стеком и очередью
int main() {
    // ... (код main остается без изменений)
    return 0;
}