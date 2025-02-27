#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d\n", root->key);
        printInOrder(root->right);
    }
}

void printLevelOrderUtil(struct Node* root, int level, struct Node* parent, char side) {
    if (root == NULL)
        return;
    if (level == 1) {
        // Check if the current node is the root
        if (parent != NULL)
            printf("%d (%d %c) (%d B) ", root->key, parent->key, side, getBalance(root));
        else
            printf("%d (%d B)", root->key, getBalance(root));
    } else if (level > 1) {
        printLevelOrderUtil(root->left, level - 1, root, 'L');
        printLevelOrderUtil(root->right, level - 1, root, 'R');
    }
}

void printLevelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevelOrderUtil(root, i, NULL, ' ');
        printf("\n");
    }
}

int main() {
    struct Node* root = NULL;
    int num;

    while (1) {
        scanf("%d", &num);
        if (num == -1)
            break;
        root = insert(root, num);
    }

    printInOrder(root);

    printf("\n");
    printLevelOrder(root);

    return 0;
}
