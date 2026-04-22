#include <stdio.h>
#include <stdlib.h>

typedef struct B2Node {
    int key;
    struct B2Node* left;
    struct B2Node* right;
    int Bal;
} B2Node;

int VR = 0;
int HR = 0;

B2Node* createB2Node(int key) {
    B2Node* node = (B2Node*)malloc(sizeof(B2Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->Bal = 0;
    return node;
}

void B2INSERT(int D, B2Node** p) {
    if (*p == NULL) {
        *p = createB2Node(D);
        VR = 1;
        HR = 0;
    } else if ((*p)->key > D) {
        B2INSERT(D, &((*p)->left));
        if (VR == 1) {
            if ((*p)->Bal == 0) {
                B2Node* q = (*p)->left;
                (*p)->left = q->right;
                q->right = *p;
                *p = q;
                q->Bal = 1;
                VR = 0;
                HR = 1;
            } else {
                (*p)->Bal = 0;
                VR = 1;
                HR = 0;
            }
        } else {
            HR = 0;
        }
    } else if ((*p)->key < D) {
        B2INSERT(D, &((*p)->right));
        if (VR == 1) {
            (*p)->Bal = 1;
            HR = 1;
            VR = 0;
        } else {
            if (HR == 1) {
                if ((*p)->Bal == 1) {
                    B2Node* q = (*p)->right;
                    (*p)->Bal = 0;
                    q->Bal = 0;
                    (*p)->right = q->left;
                    q->left = *p;
                    *p = q;
                    VR = 1;
                    HR = 0;
                } else {
                    HR = 0;
                }
            }
        }
    }
}

void printTreePretty(B2Node* root, int depth, char* prefix, int isLeft) {
    if (root == NULL) return;
    
    char newPrefix[100];
    sprintf(newPrefix, "%s%s", prefix, isLeft ? "│   " : "    ");
    printTreePretty(root->right, depth + 1, newPrefix, 0);
    
    printf("%s", prefix);
    printf("%s", isLeft ? "└── " : "┌── ");
    printf("%d(%d)\n", root->key, root->Bal);
    
    sprintf(newPrefix, "%s%s", prefix, isLeft ? "    " : "│   ");
    printTreePretty(root->left, depth + 1, newPrefix, 1);
}

void printTree(B2Node* root) {
    if (root == NULL) {
        printf("(пустое дерево)\n");
        return;
    }
    printf("\n");
    printTreePretty(root, 0, "", 0);
}

int main() {
    B2Node* root = NULL;
    int keys[] = {19, 10, 15, 24, 1, 14, 23, 13, 22, 3, 8, 5};
    char* letters[] = {"С","И","Н","Ц","А","М","Х","Л","Ф","В","Ж","Д"};
    int n = 12;

    printf("=== ПОШАГОВОЕ ПОСТРОЕНИЕ ДБД ===\n");
    for (int i = 0; i < n; i++) {
        VR = 0; HR = 0;
        printf("\nШаг %d: Вставка %s (%d)\n", i+1, letters[i], keys[i]);
        B2INSERT(keys[i], &root);
        printTree(root);
        printf("VR=%d, HR=%d\n", VR, HR);
    }

    printf("\n\n=== ИТОГОВОЕ ДЕРЕВО ===\n");
    printTree(root);

    // Расшифровка чисел в буквы
    printf("\n\n=== РАСШИФРОВКА (число → буква) ===\n");
    printf("19=С, 10=И, 15=Н, 24=Ц, 1=А, 14=М, 23=Х, 13=Л, 22=Ф, 3=В, 8=Ж, 5=Д\n");

    return 0;
}