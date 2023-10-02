#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *CreateTree(struct Node *root, int data) {
    if (root == NULL) {
        root = (struct Node *)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    } else if (data > root->data) {
        root->right = CreateTree(root->right, data);
    } // Игнорируем дублирующиеся значения

    return root;
}

int CountOccurrences(struct Node *root, int target) {
    if (root == NULL)
        return 0;

    if (root->data == target)
        return 1 + CountOccurrences(root->left, target) + CountOccurrences(root->right, target);
    else if (target < root->data)
        return CountOccurrences(root->left, target);
    else
        return CountOccurrences(root->right, target);
}

void print_tree(struct Node *r, int l) {
    if (r == NULL)
        return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;

    struct Node *root = NULL;

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        } else {
            root = CreateTree(root, D);
        }
    }

    print_tree(root, 0);

    printf("Введите значение для подсчета вхождений: ");
    scanf("%d", &D);

    int count = CountOccurrences(root, D);

    printf("Значение %d встречается %d раз(а) в дереве.\n", D, count);

    return 0;
}
