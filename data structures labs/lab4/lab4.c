#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[50];
    struct Node* next;
};

typedef struct {
    struct Node* top;
} Stack;

void push(Stack* stack, const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strncpy(newNode->data, data, sizeof(newNode->data));
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(Stack* stack) {
    if (stack->top != NULL) {
        struct Node* temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
}

const char* peek(Stack* stack) {
    return (stack->top == NULL) ? NULL : stack->top->data;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
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

void checkHtmlValidity(const char* htmlCode) {
    Stack stack;
    stack.top = NULL;

    const char* tag;
    char openingTag[50], closingTag[50];
    int errorFound = 0;

    while ((tag = strpbrk(htmlCode, "<>")) != NULL && !errorFound) {
        if (*tag == '<') {
            if (*(tag + 1) == '/') {
                sscanf(tag, "</%[^>]>", closingTag);

                if (!isEmpty(&stack)) {
                    if (strcmp(closingTag, peek(&stack)) == 0) {
                        pop(&stack);
                    } else {
                        printf("error <%s>\n", peek(&stack));

                        pop(&stack);
                        errorFound = 1;
                    }
                } else {
                    printf("error </%s>\n", closingTag);
                    errorFound = 1;
                }
            } else {
                sscanf(tag, "<%[^>]>", openingTag);
                push(&stack, strdup(openingTag));
            }
        }

        htmlCode = tag + 1;
    }

    if (!errorFound) {
        while (!isEmpty(&stack)) {
            printf("error <%s>\n", peek(&stack));
            pop(&stack);
        }

        if (isEmpty(&stack)) {
            printf("correct\n");
        }
    }
}

int main() {
    char htmlCode[500];
    fgets(htmlCode, sizeof(htmlCode), stdin);

    checkHtmlValidity(htmlCode);

    return 0;
}
