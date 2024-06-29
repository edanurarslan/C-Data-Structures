#include <stdio.h>
#include <stdlib.h>

struct Ogrenci {
    int numara;
    int not;
    struct Ogrenci* sol;
    struct Ogrenci* sag;
};

struct Ogrenci* ogrenciEkle(struct Ogrenci* root, int numara, int not) {
    if (root == NULL) {
        struct Ogrenci* yeniOgrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
        yeniOgrenci->numara = numara;
        yeniOgrenci->not = not;
        yeniOgrenci->sol = yeniOgrenci->sag = NULL;
        return yeniOgrenci;
    }

    if (not < root->not) {
        root->sol = ogrenciEkle(root->sol, numara, not);
    } else if (not > root->not) {
        root->sag = ogrenciEkle(root->sag, numara, not);
    }

    return root;
}

void siraliYazdir(struct Ogrenci* root) {
    if (root != NULL) {
        siraliYazdir(root->sol);
        printf("%d %d\n", root->numara, root->not);
        siraliYazdir(root->sag);
    }
}

struct Node {
    int x, y;
    struct Node* left;
    struct Node* right;
    char position;
    int parentY;
};

void printLevel(struct Node* root, int level) {
    if (root == NULL)
        return;

    if (level == 1) {
        if (root->parentY != -1) {
            printf("%d %d (%d %c) ", root->x, root->y, root->parentY, root->position);
        } else {
            printf("%d %d ", root->x, root->y);
        }
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

int height(struct Node* root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

void printTree(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
        printf("\n");
    }
}

struct Node* insert(struct Node* root, int x, int y, int parentY, char position) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->x = x;
        newNode->y = y;
        newNode->left = newNode->right = NULL;
        newNode->position = position;
        newNode->parentY = parentY;
        return newNode;
    }

    if (y < root->y) {
        root->left = insert(root->left, x, y, root->y, 'L');
    } else if (y > root->y) {
        root->right = insert(root->right, x, y, root->y, 'R');
    }

    return root;
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Ogrenci* ogrenciRoot = NULL;
    struct Node* nodeRoot = NULL;
    int numara, not, x, y;

    while (1) {
        scanf("%d", &numara);

        if (numara == -1)
            break;

        scanf("%d", &not);
        ogrenciRoot = ogrenciEkle(ogrenciRoot, numara, not);
        nodeRoot = insert(nodeRoot, numara, not, -1, ' ');
    }

    siraliYazdir(ogrenciRoot);
    printf("\n");
    printTree(nodeRoot);

    freeTree(nodeRoot);
    freeTree(ogrenciRoot);

    return 0;
}
