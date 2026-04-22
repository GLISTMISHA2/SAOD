#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SYM 2048 
#define MAX_CODE 64

unsigned int utf8_get(FILE *f) {
    int c = fgetc(f);
    if (c == EOF) return EOF;

    if ((c & 0x80) == 0) {
        return c;
    }

    if ((c & 0xE0) == 0xC0) {
        int c2 = fgetc(f);
        if (c2 == EOF) return EOF;
        return ((c & 0x1F) << 6) | (c2 & 0x3F);
    }

    if ((c & 0xF0) == 0xE0) {
        int c2 = fgetc(f), c3 = fgetc(f);
        if (c2 == EOF || c3 == EOF) return EOF;
        return ((c & 0x0F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
    }

    return c;
}

int main() {
    FILE *f = fopen("text.txt", "rb");
    if (!f) {
        printf("Не удалось открыть text.txt\n");
        return 1;
    }

    unsigned int symbols[MAX_SYM];
    long count[MAX_SYM] = {0};
    int used = 0;

    long total = 0;
    unsigned int s;

    while ((s = utf8_get(f)) != EOF) {
        int found = -1;
        for (int i = 0; i < used; i++) {
            if (symbols[i] == s) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            symbols[used] = s;
            count[used] = 1;
            used++;
        } else {
            count[found]++;
        }

        total++;
    }
    fclose(f);

    double P[MAX_SYM], Q[MAX_SYM];
    int L[MAX_SYM];
    int C[MAX_SYM][MAX_CODE];

    int n = used;

    for (int i = 0; i < n; i++)
        P[i] = (double)count[i] / total;

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (P[j] > P[i]) {
                double tp = P[i]; P[i] = P[j]; P[j] = tp;
                unsigned int ts = symbols[i]; symbols[i] = symbols[j]; symbols[j] = ts;
                long tc = count[i]; count[i] = count[j]; count[j] = tc;
            }

    Q[0] = 0;
    for (int i = 1; i <= n; i++)
        Q[i] = Q[i-1] + P[i-1];

    for (int i = 0; i < n; i++)
        L[i] = (int)ceil(-log2(P[i]));

    for (int i = 0; i < n; i++) {
        double q = Q[i];
        for (int j = 0; j < L[i]; j++) {
            q *= 2;
            C[i][j] = (int)floor(q);
            if (q >= 1) q -= 1;
        }
    }
printf(" _________________________________________________________\n");
printf("| i |Символ|   P(i)    |   Q(i)   | Li | Код Шеннона      |\n");
printf("|___|______|___________|__________|____|__________________|\n");

for (int i = 0; i < n; i++) {
    printf("|%2d |  ", i+1);

    unsigned int u = symbols[i];
    if (u < 128) {
        printf(" %c ", (char)u);
    } else if (u <= 0x7FF) {
        printf(" %c%c ", 
            (char)(0xC0 | ((u >> 6) & 0x1F)),
            (char)(0x80 | (u & 0x3F))
        );
    } else {
        printf(" %c%c%c ",
            (char)(0xE0 | ((u >> 12) & 0x0F)),
            (char)(0x80 | ((u >> 6) & 0x3F)),
            (char)(0x80 | (u & 0x3F))
        );
    }

    char code_str[MAX_CODE + 1];
    for (int j = 0; j < L[i]; j++)
        code_str[j] = C[i][j] ? '1' : '0';
    code_str[L[i]] = '\0';

    printf(" | %9.6f | %8.6f | %2d | %-16s |\n",
           P[i], Q[i], L[i], code_str);
}

printf("|___|______|___________|__________|____|__________________|\n");

double kraft_sum = 0;
double entropy = 0;
double avg_len = 0;

for (int i = 0; i < n; i++) {
    kraft_sum += pow(2, -L[i]);         
    entropy -= P[i] * log2(P[i]);       
    avg_len += P[i] * L[i];             
}

double redundancy = avg_len - entropy;  

printf("\n _____________________________________________________________________________\n");
printf("|%-10s| %-10s |%-10s|%-10s|\n", "Нерав-во Крафта", "Энтропия", 
       "Ср. длина кодового слова", "Избыточность кода Шеннона");
printf("|_______________|__________|________________________|_________________________|\n");
printf("| %13.6f |%10.6f| %22.6f | %23.6f |\n", kraft_sum, entropy, avg_len, redundancy);
printf("|_______________|__________|________________________|_________________________|\n");
f = fopen("text.txt", "rb");
if (!f) {
    printf("Не удалось открыть text.txt\n");
    return 1;
}

printf("\nЗакодированная последовательность (для первых 100 символов):\n");

int max_chars = 100;
int char_count = 0;
long encoded_bits = 0;
unsigned int ch;

while (char_count < max_chars && (ch = utf8_get(f)) != EOF) {
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (symbols[i] == ch) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        for (int j = 0; j < L[idx]; j++)
            printf("%d", C[idx][j]);
        encoded_bits += L[idx];
    }
    char_count++;
}

fclose(f);

printf("\n\nДлина закодированной последовательности: %ld бит\n", encoded_bits);

long original_bits = max_chars * 8;
double compression_ratio = (double)original_bits / encoded_bits;

printf("Коэффициент сжатия: %.3f\n", compression_ratio);
}