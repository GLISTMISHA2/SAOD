#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

#define RECORDS_PER_PAGE 20
#define MAX_RECORDS 4000

typedef struct {
    char accountNumber[10];
    char fullName[50];
    char address[50];
    double depositAmount;
    char depositDate[10];
    char lawyerName[50];
    char lawyerPhone[15];
} Depositor;

Depositor depositors[MAX_RECORDS];
Depositor* sortedByLawyer[MAX_RECORDS];
int recordCount = 0;

void clear_input() {
    while (getchar() != '\n');
}

char* cp866_to_utf8(const char* cp866_str) {
    if (!cp866_str) return NULL;
    
    int wlen = MultiByteToWideChar(866, 0, cp866_str, -1, NULL, 0);
    wchar_t* wstr = malloc(wlen * sizeof(wchar_t));
    MultiByteToWideChar(866, 0, cp866_str, -1, wstr, wlen);
    int ulen = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* utf8_str = malloc(ulen);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8_str, ulen, NULL, NULL);
    free(wstr);
    return utf8_str;
}

void init_console() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

int string_compare(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int compare_by_lawyer(const void* a, const void* b) {
    Depositor* depA = *(Depositor**)a;
    Depositor* depB = *(Depositor**)b;
    return string_compare(depA->lawyerName, depB->lawyerName);
}

void merge(Depositor** arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Depositor** leftArr = malloc(n1 * sizeof(Depositor*));
    Depositor** rightArr = malloc(n2 * sizeof(Depositor*));

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (compare_by_lawyer(&leftArr[i], &rightArr[j]) <= 0) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

void merge_sort(Depositor** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void display_single_record(Depositor* record, int index) {
    char* name_utf8 = cp866_to_utf8(record->fullName);
    char* lawyer_utf8 = cp866_to_utf8(record->lawyerName);
    char* address_utf8 = cp866_to_utf8(record->address);
    
    printf("\n=== ЗАПИСЬ №%d ===\n", index);
    printf("Номер счета: %s\n", record->accountNumber);
    printf("ФИО вкладчика: %s\n", name_utf8);
    printf("Адрес: %s\n", address_utf8);
    printf("Сумма вклада: %.2f\n", record->depositAmount);
    printf("Дата вклада: %s\n", record->depositDate);
    printf("ФИО адвоката: %s\n", lawyer_utf8);
    printf("Телефон адвоката: %s\n", record->lawyerPhone);
    printf("==============================\n");
    
    free(name_utf8);
    free(lawyer_utf8);
    free(address_utf8);
}

void display_records(Depositor** records, int count, int is_sorted) {
    int pos = 0;
    char input;
    
    printf("\n=== %sБАЗА ДАННЫХ (%d записей) ===\n", 
           is_sorted ? "ОТСОРТИРОВАННАЯ " : "", count);
    
    while (pos < count) {
        printf("\n--- Страница %d ---\n", (pos / RECORDS_PER_PAGE) + 1);
        
        for (int i = 0; i < RECORDS_PER_PAGE && pos < count; i++, pos++) {
            char* name_utf8 = cp866_to_utf8(records[pos]->fullName);
            char* lawyer_utf8 = cp866_to_utf8(records[pos]->lawyerName);
            
            printf("%4d. | Счет: %-10s | Вкладчик: %-30s\n", 
                  pos + 1, 
                  records[pos]->accountNumber, 
                  name_utf8);
            printf("     | Сумма: %10.2f | Адвокат: %-30s\n", 
                  records[pos]->depositAmount, lawyer_utf8);
            printf("     | %s\n", "----------------------------------------------");
                  
            free(name_utf8);
            free(lawyer_utf8);
        }

        if (pos < count) {
            printf("\nПоказать следующую страницу? (y/n): ");
            input = tolower(getchar());
            clear_input();
            if (input == 'n') break;
        }
    }
    printf("\nПоказано записей: %d из %d\n", pos, count);
}

void search_and_display_record() {
    int record_num;
    
    printf("\n=== ПОИСК ЗАПИСИ В ОТСОРТИРОВАННОЙ БАЗЕ ===\n");
    printf("Введите номер записи (1-%d): ", recordCount);
    
    if (scanf("%d", &record_num) != 1) {
        printf("Ошибка ввода!\n");
        clear_input();
        return;
    }
    clear_input();
    
    if (record_num < 1 || record_num > recordCount) {
        printf("Номер должен быть от 1 до %d!\n", recordCount);
        return;
    }
    
    display_single_record(sortedByLawyer[record_num - 1], record_num);
}

void display_original_database() {
    Depositor* originalOrder[MAX_RECORDS];
    for (int i = 0; i < recordCount; i++) {
        originalOrder[i] = &depositors[i];
    }
    display_records(originalOrder, recordCount, 0);
}

void display_sorted_database() {
    display_records(sortedByLawyer, recordCount, 1);
}

int main() {
    init_console();
    
    FILE* fp = fopen("testBase1.dat", "rb");
    if (!fp) {
        printf("Ошибка открытия файла testBase1.dat!\n");
        return 1;
    }
    
    recordCount = fread(depositors, sizeof(Depositor), MAX_RECORDS, fp);
    fclose(fp);
    
    printf("Загружено записей: %d\n", recordCount);
    
    for (int i = 0; i < recordCount; i++) {
        sortedByLawyer[i] = &depositors[i];
    }
    
    merge_sort(sortedByLawyer, 0, recordCount - 1);
    
    int choice;
    do {
        printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("1. Вывод оригинальной базы данных\n");
        printf("2. Вывод отсортированной базы данных (по адвокату)\n");
        printf("3. Вывод конкретной записи из отсортированной базы\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            clear_input();
            continue;
        }
        clear_input();
        
        switch (choice) {
            case 1:
                display_original_database();
                break;
            case 2:
                display_sorted_database();
                break;
            case 3:
                search_and_display_record();
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}