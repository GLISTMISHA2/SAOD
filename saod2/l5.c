#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertDoubleIndirect(Node** root, int key) {
    Node** current = root;
    
    while (*current != NULL) {
        if (key < (*current)->key) {
            current = &(*current)->left;
        } else if (key > (*current)->key) {
            current = &(*current)->right;
        } else {
            return; 
        }
    }
    
    *current = createNode(key);
}

Node* findMin(Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

void deleteDoubleIndirect(Node** root, int key) {
    Node** current = root;
    
    while (*current != NULL) {
        if (key < (*current)->key) {
            current = &(*current)->left;
        } else if (key > (*current)->key) {
            current = &(*current)->right;
        } else {
            Node* toDelete = *current;
            if (toDelete->left == NULL) {
                *current = toDelete->right;
                free(toDelete);
            } else if (toDelete->right == NULL) {
                *current = toDelete->left;
                free(toDelete);
            } else {
                Node* minNode = findMin(toDelete->right);
                
                toDelete->key = minNode->key;
                
                deleteDoubleIndirect(&toDelete->right, minNode->key);
            }
            break;
        }
    }
}

// Обход слева направо (симметричный)
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

// ОБХОД СВЕРХУ-ВНИЗ (ПРЯМОЙ ОБХОД - PRE-ORDER)
void topDownTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);           // Сначала корень
        topDownTraversal(root->left);       // Потом левое поддерево
        topDownTraversal(root->right);      // Потом правое поддерево
    }
}

// Вычисление характеристик дерева
int getSize(Node* root) {
    if (root == NULL) return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

int getChecksum(Node* root) {
    if (root == NULL) return 0;
    return root->key + getChecksum(root->left) + getChecksum(root->right);
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    int left = getHeight(root->left);
    int right = getHeight(root->right);
    return 1 + (left > right ? left : right);
}

int getTotalHeight(Node* root, int depth) {
    if (root == NULL) return 0;
    return depth + getTotalHeight(root->left, depth + 1) + getTotalHeight(root->right, depth + 1);
}

double getAverageHeight(Node* root) {
    int size = getSize(root);
    if (size == 0) return 0.0;
    return (double)getTotalHeight(root, 1) / size;
}

// Генерация случайной последовательности
void generateRandomSequence(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    // Перемешиваем Фишером-Йейтсом
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Функция для красивого вывода дерева (вертикальный обход)
void printTree(Node* root, int space) {
    if (root == NULL) return;
    
    // Увеличиваем отступ
    space += 5;
    
    // Сначала правый ребенок
    printTree(root->right, space);
    
    // Текущий узел
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);
    
    // Левый ребенок
    printTree(root->left, space);
}

// Основная функция
int main() {
    srand(time(NULL));
    const int n = 100;
    int sequence[n];
    
    
    generateRandomSequence(sequence, n);
   
    // printf("Последовательность для построения СДП: ");
    // for (int i = 0; i < 10; i++) {  
    //     printf("%d ", sequence[i]);
    // }
    // printf("...\n\n");
    
    Node* sdpRoot = NULL;
    
    for (int i = 0; i < n; i++) {
        insertDoubleIndirect(&sdpRoot, sequence[i]);
    }
  
    printf("Обход СДП слева направо: ");
    inOrderTraversal(sdpRoot);
    printf("\n\n");
    
    printf("Обход СДП сверху-вниз: ");
    topDownTraversal(sdpRoot);
    printf("\n\n");
    
    printf("| n=%d | Размер | Контр.сумма | Высота | Средн.высота |\n", n);
    printf("|-------|--------|-------------|--------|--------------|\n");
    
    printf("| СДП   | %6d | %11d | %6d | %12.2f |\n", 
           getSize(sdpRoot), getChecksum(sdpRoot), 
           getHeight(sdpRoot), getAverageHeight(sdpRoot));
    
    printf("\nУДАЛЕНИЕ 10 ВЕРШИН ИЗ СДП\n");
    
    for (int i = 0; i < 10; i++) {
        int keyToDelete;
        printf("\nВведите ключ для удаления %d: ", i + 1);
        scanf("%d", &keyToDelete);
        
        printf("Удаляем вершину с ключом %d...\n", keyToDelete);
   
        deleteDoubleIndirect(&sdpRoot, keyToDelete);

        printf("Обход сверху-вниз после удаления: ");
        topDownTraversal(sdpRoot);
        printf("\n");

        printf("Обход СДП слева направо: ");
        inOrderTraversal(sdpRoot);
        printf("\n\n");
        

        printf("Размер: %d, Контр.сумма: %d, Высота: %d, Средняя высота: %.2f\n",
               getSize(sdpRoot), getChecksum(sdpRoot), getHeight(sdpRoot), getAverageHeight(sdpRoot));
        
        printf("------------------------\n");
    }
    
    return 0;
}