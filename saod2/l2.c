#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void topDownTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    topDownTraversal(root->left);
    topDownTraversal(root->right);
}

void leftRightTraversal(TreeNode* root) {
    if (root == NULL) return;
    leftRightTraversal(root->left);
    printf("%d ", root->data);
    leftRightTraversal(root->right);
}

void bottomUpTraversal(TreeNode* root) {
    if (root == NULL) return;
    bottomUpTraversal(root->left);
    bottomUpTraversal(root->right);
    printf("%d ", root->data);
}

int treeSize(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + treeSize(root->left) + treeSize(root->right);
}

int treeChecksum(TreeNode* root) {
    if (root == NULL) return 0;
    return root->data + treeChecksum(root->left) + treeChecksum(root->right);
}

int treeHeight(TreeNode* root) {
    if (root == NULL) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void averageHeightHelper(TreeNode* root, int level, int* sum, int* count) {
    if (root == NULL) return;
    *sum += level;
    (*count)++;
    averageHeightHelper(root->left, level + 1, sum, count);
    averageHeightHelper(root->right, level + 1, sum, count);
}

float treeAverageHeight(TreeNode* root) {
    int sum = 0, count = 0;
    averageHeightHelper(root, 0, &sum, &count); // с уровня 0 для корня
    return (float)sum / count;
}

TreeNode* createYourTree() {
    TreeNode* n1 = createNode(1);
    TreeNode* n2 = createNode(2);
    TreeNode* n3 = createNode(3);
    TreeNode* n4 = createNode(4);
    TreeNode* n5 = createNode(5);
    TreeNode* n6 = createNode(6);
    
    // 1 -> 2 (вправо), 2 -> 3 (влево), 3 -> 4 (вправо), 4 -> 5 (влево), 5 -> 6 (вправо)
    n1->right = n2;  // от 1 к 2 вправо
    n2->left = n3;   // от 2 к 3 влево
    n3->right = n4;  // от 3 к 4 вправо
    n4->left = n5;   // от 4 к 5 влево
    n5->right = n6;  // от 5 к 6 вправо
    
    return n1;
}

int main() {
    TreeNode* root = createYourTree();

    printf("Обход сверху вниз: ");
    topDownTraversal(root);
    printf("\n");
    
    printf("Обход слева направо: ");
    leftRightTraversal(root);
    printf("\n");
    
    printf("Обход снизу вверх: ");
    bottomUpTraversal(root);
    printf("\n\n");

    int size = treeSize(root);
    int checksum = treeChecksum(root);
    int height = treeHeight(root);
    float avgHeight = treeAverageHeight(root);

    printf("Характеристики дерева:\n");
    printf("Размер: %d\n", size);
    printf("Контрольная сумма: %d\n", checksum);
    printf("Высота: %d\n", height);
    printf("Средняя высота: %.2f\n", avgHeight);
    
    return 0;
}