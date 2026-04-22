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

Node* insertRecursive(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    
    if (key < root->key) {
        root->left = insertRecursive(root->left, key);
    } else if (key > root->key) {
        root->right = insertRecursive(root->right, key);
    }
    
    return root;
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

Node* IBST(int L, int R) {
    if (L > R) return NULL;
    int m = (int)ceil((double)(L + R) / 2.0);
    Node* p = createNode(0);
    p->left = IBST(L, m - 1);
    p->right = IBST(m + 1, R);
    return p;
}

Node* buildIBST(int n) {
    return IBST(1, n);
}

void numberVertices(Node* root) {
    if (!root) return;
    Node* queue[200];
    int front = 0, back = 0, num = 1;
    queue[back++] = root;
    while (front < back) {
        Node* cur = queue[front++];
        cur->key = num++;
        if (cur->left) queue[back++] = cur->left;
        if (cur->right) queue[back++] = cur->right;
    }
}

void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

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

void generateRandomSequence(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}



int main() {
    srand(time(NULL));
    const int n = 100;
    int sequence[n];
    
    generateRandomSequence(sequence, n);
    
    Node* isdpRoot = buildIBST(n);
    numberVertices(isdpRoot);
    
    Node* sdp1Root = NULL;
    Node* sdp2Root = NULL;

    for (int i = 0; i < n; i++) {
        sdp1Root = insertRecursive(sdp1Root, sequence[i]);
        insertDoubleIndirect(&sdp2Root, sequence[i]);
    }
    
    printf("Обход ИСДП: ");
    inOrderTraversal(isdpRoot);
    printf("\n\n");
    
    printf("Обход СДП1 рекурсивно: ");
    inOrderTraversal(sdp1Root);
    printf("\n\n");
    
    printf("Обход СДП2 c двойной косвенностью: ");
    inOrderTraversal(sdp2Root);
    printf("\n\n");
    
    printf("| n=%d | Размер | Контр.сумма | Высота | Средн.высота |\n", n);
    printf("|=======|========|=============|========|==============|\n");
    printf("| ИСДП  | %6d | %11d | %6d | %12.2f |\n", 
           getSize(isdpRoot), getChecksum(isdpRoot), 
           getHeight(isdpRoot), getAverageHeight(isdpRoot));
    
    printf("| СДП1  | %6d | %11d | %6d | %12.2f |\n", 
           getSize(sdp1Root), getChecksum(sdp1Root), 
           getHeight(sdp1Root), getAverageHeight(sdp1Root));
    
    printf("| СДП2  | %6d | %11d | %6d | %12.2f |\n", 
           getSize(sdp2Root), getChecksum(sdp2Root), 
           getHeight(sdp2Root), getAverageHeight(sdp2Root));
    freeTree(isdpRoot);
    freeTree(sdp1Root);
    freeTree(sdp2Root);
    
    return 0;
}