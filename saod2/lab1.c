#include <stdio.h>
#include <string.h>
#include <math.h>

int comparison_count =0;

void reset_counter() {
    comparison_count=0;
}
void direct(const char* text, const char* pattern) {
    printf("   МЕТОД ПЕРЕБОРА \n");
    printf("Подстрока: %s\n",pattern);
    printf("Индексы вхождений: ");
    
    reset_counter();
    int n = strlen(text);
    int m = strlen(pattern);
    int found = 0;
    
    if (m==0 || n<m) {
        printf("не найдено");
        printf("\nКоличество сравнений: 0\n\n");
        return;
    }
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            comparison_count++;
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            printf("%d ", i);
            found++;
        }
    }
    
    if (!found) {
        printf("не найдено");
    }
    printf("\nКоличество сравнений: %d\n\n", comparison_count);
}
void rabin_karp(const char* text, const char* pattern) {
    printf("   МЕТОД РАБИНА-КАРПА \n");
    printf("Подстрока: %s\n", pattern);
    printf("Индексы вхождений: ");
    
    reset_counter();
    int n = strlen(text);
    int m = strlen(pattern);
    int found = 0;
    
    if (m == 0 || n < m) {
        printf("не найдено");
        printf("\nКоличество сравнений: 0\n\n");
        return;
    }
    int prime = 101;
    int d = 256;
    
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % prime;
    }
    
    int hash_pattern = 0;
    int hash_text = 0;
    for (int i = 0; i < m; i++) {
        hash_pattern = (d * hash_pattern + pattern[i]) % prime;
        hash_text = (d * hash_text + text[i]) % prime;
    }
    
    for (int i = 0; i <= n - m; i++) {
        if (hash_pattern == hash_text) {
            int j;
            for (j = 0; j < m; j++) {
                comparison_count++;
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("%d ", i);
                found++;
            }
        }
        if (i < n - m) {
            hash_text = (d * (hash_text - text[i] * h) + text[i + m]) % prime;
            if (hash_text < 0) {
                hash_text += prime;
            }
        }
    }
    
    if (!found) {
        printf("не найдено");
    }
    printf("\nКоличество сравнений: %d\n\n", comparison_count);

}
/*The quick brown fox jumps over the lazy dog. The dog barks at the fox but the fox keeps jumping. Jumping is what foxes do best. They jump over fences, they jump over streams, they jump over dogs.The lazy dog doesn't like jumping. The dog prefers sleeping. Sleeping is good for lazy dogs. Quick foxes are always jumping. Brown foxes, red foxes, all kinds of foxes enjoy jumping. The quick brown fox jumps over and over again. Jump, jump, jump - that's the fox's motto.Meanwhile the lazy dog sleeps and dreams. Dreams of chasing foxes? Maybe. But mostly dreams of sleeping. The dog is lazy, very lazy. Too lazy to jump. Too lazy to chase. Just lazy. So the fox keeps jumping over the lazy dog. Day after day. Jump after jump. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. This is a famous sentence with every letter. Jumping fox, sleeping dog. This is the story of their lives. Fox jumps, dog sleeps. Will the dog ever wake up? Will the fox ever stop jumping? Only time will tell. But for now: the quick brown fox jumps over the lazy dog. Again and again. Jumping is eternal for foxes. Sleeping is eternal for lazy dogs. This is the way of the world. Fox jumps. Dog sleeps. Repeat. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."*/
int main() {
    const char* text = "The quick brown fox jumps over the lazy dog. The dog barks at the fox but the fox keeps jumping. Jumping is what foxes do best. They jump over fences, they jump over streams, they jump over dogs.The lazy dog doesn't like jumping. The dog prefers sleeping. Sleeping is good for lazy dogs. Quick foxes are always jumping. Brown foxes, red foxes, all kinds of foxes enjoy jumping. The quick brown fox jumps over and over again. Jump, jump, jump - that's the fox's motto.Meanwhile the lazy dog sleeps and dreams. Dreams of chasing foxes? Maybe. But mostly dreams of sleeping. The dog is lazy, very lazy. Too lazy to jump. Too lazy to chase. Just lazy. So the fox keeps jumping over the lazy dog. Day after day. Jump after jump. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. This is a famous sentence with every letter. Jumping fox, sleeping dog. This is the story of their lives. Fox jumps, dog sleeps. Will the dog ever wake up? Will the fox ever stop jumping? Only time will tell. But for now: the quick brown fox jumps over the lazy dog. Again and again. Jumping is eternal for foxes. Sleeping is eternal for lazy dogs. This is the way of the world. Fox jumps. Dog sleeps. Repeat. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char pattern[100];
    printf("Длина текста: %lu символов\n", strlen(text));
    printf("The quick brown fox jumps over the lazy dog. The dog barks at the fox but the fox keeps jumping. Jumping is what foxes do best. They jump over fences, they jump over streams, they jump over dogs.The lazy dog doesn't like jumping. The dog prefers sleeping. Sleeping is good for lazy dogs. Quick foxes are always jumping. Brown foxes, red foxes, all kinds of foxes enjoy jumping. The quick brown fox jumps over and over again. Jump, jump, jump - that's the fox's motto.Meanwhile the lazy dog sleeps and dreams. Dreams of chasing foxes? Maybe. But mostly dreams of sleeping. The dog is lazy, very lazy. Too lazy to jump. Too lazy to chase. Just lazy. So the fox keeps jumping over the lazy dog. Day after day. Jump after jump. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. This is a famous sentence with every letter. Jumping fox, sleeping dog. This is the story of their lives. Fox jumps, dog sleeps. Will the dog ever wake up? Will the fox ever stop jumping? Only time will tell. But for now: the quick brown fox jumps over the lazy dog. Again and again. Jumping is eternal for foxes. Sleeping is eternal for lazy dogs. This is the way of the world. Fox jumps. Dog sleeps. Repeat. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    printf("\n\nВведите подстроку для поиска: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';
    printf("\n");

    direct(text, pattern);
    int brute_force_comparisons = comparison_count;
    rabin_karp(text, pattern);
    int rabin_karp_comparisons = comparison_count;
    printf("   ЭФЕКТИВНОСТЬ МЕТОДОВ \n");
    printf("Метод перебора: %d сравнений\n", brute_force_comparisons);
    printf("Метод Рабина-Карпа: %d сравнений\n", rabin_karp_comparisons);

    if (brute_force_comparisons == 0 && rabin_karp_comparisons == 0) {
        printf("Оба метода не выполнили сравнений\n");
    } else if (brute_force_comparisons == 0) {
        printf("Метод перебора не выполнил сравнений\n");
    } else if (rabin_karp_comparisons == 0) {
        printf("Метод Рабина-Карпа не выполнил сравнений\n");
    } else {
        double ratio = (double)brute_force_comparisons / rabin_karp_comparisons;
        printf("Метод Рабина-Карпа эффективнее в %.2f раз\n", ratio);
        
        if (brute_force_comparisons < rabin_karp_comparisons) {
            ratio = (double)rabin_karp_comparisons / brute_force_comparisons;
            printf("Метод перебора эффективнее в %.2f раз\n", ratio);
        }
    }
}