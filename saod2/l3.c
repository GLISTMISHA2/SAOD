#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertex {
    int Data;
    struct Vertex* Left;
    struct Vertex* Right;
} Vertex;

Vertex* createVertex() {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    vertex->Data = 0;
    vertex->Left = NULL;
    vertex->Right = NULL;
    return vertex;}

Vertex* IBST(int L, int R) {
    if (L > R) return NULL;
    int m = (int)ceil((double)(L + R) / 2.0);
    Vertex* p = createVertex();
    p->Left = IBST(L, m - 1);
    p->Right = IBST(m + 1, R);
    return p;
}

Vertex* buildIBST() {
    return IBST(1, 100);}

void numberVertices(Vertex* root) {
    if (!root) return;
    Vertex* queue[200];
    int front = 0, back = 0, num = 1;
    queue[back++] = root;
    while (front < back) {
        Vertex* cur = queue[front++];
        cur->Data = num++;
        if (cur->Left) queue[back++] = cur->Left;
        if (cur->Right) queue[back++] = cur->Right;}}


int size(Vertex* root) {
    if (root == NULL) return 0;
    return 1 + size(root->Left) + size(root->Right);}

int checksum(Vertex* root) {
    if (root == NULL) return 0;
    return root->Data + checksum(root->Left) + checksum(root->Right);}

int height(Vertex* root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->Left);
    int rightHeight = height(root->Right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;}

double sumPathLength(Vertex* root, int level) {
    if (root == NULL) return 0;
    return (level + sumPathLength(root->Left, level + 1) + sumPathLength(root->Right, level + 1));}

double averageHeight(Vertex* root) {
    if (root == NULL) return 0;
    return sumPathLength(root, 1) / size(root);}

void freeTree(Vertex* root) {
    if (root == NULL) return;
    freeTree(root->Left);
    freeTree(root->Right);
    free(root);}

void centric(Vertex* root) {
    if (root == NULL) return;
    centric(root->Left);
    printf("%d ", root->Data);
    centric(root->Right);}


void up(Vertex* root) {
    if (root == NULL) return;
    printf("%d ", root->Data);
    up(root->Left);
    up(root->Right);}

    
void down(Vertex* root) {
    if (root == NULL) return;
    down(root->Left);
    down(root->Right);
    printf("%d ", root->Data);}


int main() {

    Vertex* root = buildIBST();
    numberVertices(root);
    printf("ИСДП \n");

    printf("Слева направо: ");
    centric(root);
    printf("\n\n");
    printf("Размер дерева: %d\n", size(root));
    printf("Контрольная сумма: %d\n", checksum(root));
    printf("Высота дерева: %d\n", height(root));
    printf("Средняя высота: %.2f\n", averageHeight(root));}