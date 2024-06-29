#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char songName[50];
    int songNumber;
    struct node* prev;
    struct node* next;
};

typedef struct node Node;

Node* head = NULL;
Node* tail = NULL;

void addSongToList(char songName[50]) {
    Node* newSong = (Node*)malloc(sizeof(Node));
    strcpy(newSong->songName, songName);
    newSong->songNumber = 0;

    if (head == NULL) {
        head = newSong;
        tail = newSong;
        newSong->prev = NULL;
        newSong->next = NULL;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        newSong->next = NULL;
        tail = newSong;
    }
}

void printSongs(char command[2], int step) {
    Node* current = (strcmp(command, "B") == 0) ? head : tail;
    int count = 0;

    while (current != NULL) {
        if (count % step == 0) {
            printf("%s\n", current->songName);
        }
        count++;
        current = (strcmp(command, "B") == 0) ? current->next : current->prev;
    }
}

int main() {
    char songName[50];
    while (1) {
        fgets(songName, sizeof(songName), stdin);
        songName[strcspn(songName, "\n")] = '\0';

        if (strcmp(songName, "-1") == 0) {
            break;
        }

        addSongToList(songName);
    }

    char command[2];
    int step;
    scanf("%s %d", command, &step);
    printSongs(command, step+1);

    return 0;
}
