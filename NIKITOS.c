#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void append(struct node** head_ref, int data) {
    struct node* newNode = createNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void freeList(struct node* head) {
    struct node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(struct node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct node* head1 = NULL;
    struct node* head2 = NULL;
    int input, n;

    // Ввод верхнего списка
    printf("Введите количество элементов верхнего списка: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Список не может быть пустым!\n");
        return 1;
    }
    printf("Введите элементы верхнего списка:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        append(&head1, input);
    }

    // Ввод нижнего списка
    printf("Введите количество элементов нижнего списка: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Список не может быть пустым!\n");
        freeList(head1);
        return 1;
    }
    printf("Введите элементы нижнего списка:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        append(&head2, input);
    }

    struct node* current = head1;
    int isUpperList = 1;
    char command;

    while (1) {
        printf("\nТекущий элемент: %d\n", current->data);
        printf("Введите команду:\n[S/s] Переключиться в нижний список\n[A/a] Назад\n[D/d] Вперед\n[Q/q] Выход\n> ");
        scanf(" %c", &command);

        switch (command) {
            case 'D': case 'd':
                if (current->next) current = current->next;
                else printf("Достигнут конец списка!\n");
                break;

            case 'A': case 'a':
                if (isUpperList && current->prev) current = current->prev;
                else printf("Движение назад невозможно!\n");
                break;

            case 'S': case 's':
                if (isUpperList) {
                    int pos = 0;
                    struct node* tmp = head1;
                    while (tmp != current) {
                        tmp = tmp->next;
                        pos++;
                    }
                    
                    struct node* lower = head2;
                    for (int i = 0; i < pos && lower != NULL; i++) {
                        lower = lower->next;
                    }
                    
                    if (lower) {
                        current = lower;
                        isUpperList = 0;
                        printf("Переключено на нижний список\n");
                    } else {
                        printf("Нет соответствующего элемента в нижнем списке!\n");
                    }
                } else {
                    printf("Уже в нижнем списке!\n");
                }
                break;

            case 'Q': case 'q':
                freeList(head1);
                freeList(head2);
                return 0;

            default:
                printf("Некорректная команда!\n");
        }
    }
}
