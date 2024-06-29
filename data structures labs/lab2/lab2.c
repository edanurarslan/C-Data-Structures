#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct intersectedNode {
    int data;
    int index1;
    int index2;
    struct node* next;
};

// New intersectedNode created
struct intersectedNode* createIntersectedNode(int data, int index1, int index2) {
    struct intersectedNode* newnode = (struct intersectedNode*)malloc(sizeof(struct intersectedNode));
    newnode->data = data;
    newnode->index1 = index1;
    newnode->index2 = index2;
    newnode->next = NULL;
    return newnode;
}

// Insert new element to the linked list
void append(struct node** head, int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;

    if (*head == NULL) {
        *head = newnode;
    } else {
        struct node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newnode;
    }
}

// Common elements and the indexes
struct intersectedNode* findCommonElements(struct node* list1, struct node* list2) {
    int index1 = 0;
    struct intersectedNode* result = NULL;

    while (list1 != NULL) {
        int index2 = 0;
        struct node* temp2 = list2;

        while (temp2 != NULL) {
            if (list1->data == temp2->data) {
                struct intersectedNode* newnode = createIntersectedNode(list1->data, index1, index2);

                if (result == NULL) {
                    result = newnode;
                } else {
                    struct intersectedNode* current = result;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newnode;
                }
            }
            temp2 = temp2->next;
            index2++;
        }
        list1 = list1->next;
        index1++;
    }

    return result;
}

double addition(double num1, double num2) {
    return num1 + num2;
}

double subtraction(double num1, double num2) {
    return num1 - num2;
}

double multiplication(double num1, double num2) {
    return num1 * num2;
}

double division(double num1, double num2) {
    if (num2 != 0) {
        return num1 / num2;
    } else {
        printf("divison by zero\n");
        return 0.0;
    }
}

int faktoriyel(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * faktoriyel(n - 1);
}

double kare(double x) {
    return x * x;
}

int main() {
    struct node* list1 = NULL;
    struct node* list2 = NULL;
    int data;

    while (1) {
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        append(&list1, data);
    }

    while (1) {
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        append(&list2, data);
    }

    struct intersectedNode* result = findCommonElements(list1, list2);

    // Printing IntersectedNode
    struct intersectedNode* current = result;
    while (current != NULL) {
        printf("%d %d %d\n", current->data, current->index1, current->index2);
        current = current->next;
    }

    while (list1 != NULL) {
        struct node* temp = list1;
        list1 = list1->next;
        free(temp);
    }

    while (list2 != NULL) {
        struct node* temp = list2;
        list2 = list2->next;
        free(temp);
    }

    while (result != NULL) {
        struct intersectedNode* temp = result;
        result = result->next;
        free(temp);
    }

    char operator;
    double sayi1, sayi2;



    switch (operator) {
        case '+':
            printf("%.2lf + %.2lf = %.2lf\n", sayi1, sayi2, sayi1 + sayi2);
            break;
        case '-':
            printf("%.2lf - %.2lf = %.2lf\n", sayi1, sayi2, sayi1 - sayi2);
            break;
        case '*':
            printf("%.2lf * %.2lf = %.2lf\n", sayi1, sayi2, sayi1 * sayi2);
            break;
        case '/':
            if (sayi2 != 0) {
                printf("%.2lf / %.2lf = %.2lf\n", sayi1, sayi2, sayi1 / sayi2);
            } else {
                printf("divison by zero\n");
            }
            break;


    return 0;
}
}
