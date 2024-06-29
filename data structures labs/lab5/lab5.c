#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PRIORITY 17

struct Person {
    char name[MAX_NAME_LENGTH];
    int priority;
};

const char *priorityList[MAX_PRIORITY] = {
    "Annem", "Babam", "Kardesim", "Amcam", "Dayim",
    "Halam", "Teyzem", "Isyeri", "Okul", "Arkadasim1",
    "Arkadasim2", "Arkadasim3", "Arkadasim4", "Arkadasim5",
    "Banka", "Kargo", "Reklam"
};

struct PriorityQueue {
    struct Person *heap;
    int size;
    int capacity;
};

struct Person inputList[MAX_PRIORITY];
struct Person sortedList[MAX_PRIORITY];

// Function prototypes
void initializePriorityQueue(struct PriorityQueue *pq, int capacity);
void insert(struct PriorityQueue *pq, struct Person person);
struct Person extractMin(struct PriorityQueue *pq);
void printPriorityList();

int main() {
    int i;

    for (i = 0; i < MAX_PRIORITY; i++) {
        char input[MAX_NAME_LENGTH];
        int found = 0;

        scanf("%s", input);

        if (strcmp(input, "-1") == 0) {
            break;
        }

        for (int j = 0; j < MAX_PRIORITY; j++) {
            if (strcmp(input, priorityList[j]) == 0) {
                strcpy(inputList[i].name, input);
                inputList[i].priority = j;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid name! Please enter a valid name.\n");
            i--;  // Decrement i to overwrite the current index with a valid input
        }
    }

    struct PriorityQueue pq;
    initializePriorityQueue(&pq, MAX_PRIORITY);

    for (int j = 0; j < i; j++) {
        insert(&pq, inputList[j]);
    }

    for (int j = 0; j < i; j++) {
        sortedList[j] = extractMin(&pq);
        printf("%s\n", sortedList[j].name);
    }

    return 0;
}

void initializePriorityQueue(struct PriorityQueue *pq, int capacity) {
    pq->heap = (struct Person *)malloc(capacity * sizeof(struct Person));
    if (pq->heap == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    pq->size = 0;
    pq->capacity = capacity;
}

void insert(struct PriorityQueue *pq, struct Person person) {
    if (pq->size == pq->capacity) {
        printf("Error: Queue is full!\n");
        return;
    }

    int i = pq->size;
    pq->heap[i] = person;
    pq->size++;

    while (i > 0 && pq->heap[i].priority < pq->heap[(i - 1) / 2].priority) {
        // Swap elements to maintain heap property
        struct Person temp = pq->heap[i];
        pq->heap[i] = pq->heap[(i - 1) / 2];
        pq->heap[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

struct Person extractMin(struct PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Error: Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    struct Person minPerson = pq->heap[0];

    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    int i = 0;

    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int smallest = i;

        if (leftChild < pq->size && pq->heap[leftChild].priority < pq->heap[smallest].priority) {
            smallest = leftChild;
        }

        if (rightChild < pq->size && pq->heap[rightChild].priority < pq->heap[smallest].priority) {
            smallest = rightChild;
        }

        if (smallest != i) {
            // Swap elements to maintain heap property
            struct Person temp = pq->heap[i];
            pq->heap[i] = pq->heap[smallest];
            pq->heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return minPerson;
}

