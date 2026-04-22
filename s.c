#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char lastname[50];
    int age;
    int number;
};

int sortKey = 1;  
int ascending = 1; 

int Less(struct Contact a, struct Contact b) {
    int result = 0;

    if (sortKey == 1) { 
        result = strcmp(a.lastname, b.lastname);
        if (result == 0) {
            result = strcmp(a.name, b.name);
        }
    } else if (sortKey == 2) { 
        result = a.age - b.age;
        if (result == 0) {
            result = a.number - b.number;
        }
    }

    return ascending ? result : -result;
}

void InsertSort(struct Contact contacts[], int size) {
    for (int i = 1; i < size; i++) {
        struct Contact temp = contacts[i];
        int j = i - 1;

        while (j >= 0 && Less(contacts[j], temp) > 0) {
            contacts[j + 1] = contacts[j];
            j--;
        }

        contacts[j + 1] = temp;
    }
}

void printContacts(struct Contact contacts[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s, Год рождения: %d, Номер: %d\n", 
               contacts[i].lastname, contacts[i].name, contacts[i].age, contacts[i].number);
    }
    printf("\n");
}

int main() {
    struct Contact contacts[] = {
        {"Михаил", "Синица", 2007, 89529},
        {"Ибрагим", "Синица", 2000, 89293},
        {"Сергей", "Деним", 1984, 89831},
        {"Андрей", "Куплинов", 1999, 89050},
    };

    int size = sizeof(contacts) / sizeof(contacts[0]);

    printf("Исходный справочник:\n");
    printContacts(contacts, size);

    printf("Выберите ключ сортировки (1 - 'Фамилия + Имя', 2 - 'Год + Номер'): ");
    scanf("%d", &sortKey);

    printf("Выберите направление сортировки (1 - по возрастанию, 0 - по убыванию): ");
    scanf("%d", &ascending);

    InsertSort(contacts, size);

    printf("Отсортированный справочник:\n");
    printContacts(contacts, size);

    return 0;
}