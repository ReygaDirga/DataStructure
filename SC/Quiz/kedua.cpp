#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct tnode {
    char address[101];
    char id[101];
    char type[101];
    int priority;
    struct tnode* next;
} *queue = NULL;

struct tnode* createNode(char address[], char id[], char type[], int priority) {
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
    strcpy(newNode->address, address);
    strcpy(newNode->id, id);
    strcpy(newNode->type, type);
    
    if (strcmp(type, "Instant") == 0) newNode->priority = 0;
    else if (strcmp(type, "Standard") == 0) newNode->priority = 1;
    else if (strcmp(type, "Economy") == 0) newNode->priority = 2;

    newNode->next = NULL;
    return newNode;
}

void priorityQueue(struct tnode* newNode) {
    if (queue == NULL || newNode->priority < queue->priority) {
        newNode->next = queue;
        queue = newNode;
        return;
    }

    struct tnode* temp = queue;
    while (temp->next != NULL && temp->next->priority <= newNode->priority) {
        temp = temp->next;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
}

void send() {
    if (queue == NULL) {
        printf("No package to send\n");
        return;
    }

    struct tnode* temp = queue;
    printf("Sending package ID: %s, Address: %s, Type: %s\n", temp->id, temp->address, temp->type);
    queue = queue->next;
    free(temp);
}

void push() {
    char address[101], id[101], type[101];

    do {
        printf("Address: ");
        scanf(" %[^\n]", address);
    } while (strlen(address) < 8 || strlen(address) > 23 || strncmp(address, "Jl.", 3) != 0);

    sprintf(id, "CPX");
    for (int i = 3; i < 6; i++) {
        int alphaNumeric = rand() % 2;
        if (alphaNumeric == 0) {
            id[i] = 'A' + (rand() % 26);
        } else {
            id[i] = '0' + (rand() % 10);
        }
    }
    id[6] = '\0';

    do {
        printf("Type [Economy | Standard | Instant]: ");
        scanf(" %s", type);
    } while (strcmp(type, "Economy") != 0 && strcmp(type, "Standard") != 0 && strcmp(type, "Instant") != 0);

    struct tnode* newNode = createNode(address, id, type, 0);
    priorityQueue(newNode);
}

int main() {
    srand(time(NULL));
    int choice;

    do {
        printf("\n1. Add Package\n2. Send Package\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                send();
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
