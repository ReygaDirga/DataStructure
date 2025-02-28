#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[30];
    char ticket[15];
    struct Node *prev, *next;
};

struct Node *head = NULL, *tail = NULL;

struct Node* createNode(char name[], char ticket[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->ticket, ticket);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void enqueue(char name[], char ticket[]) {
    struct Node* newNode = createNode(name, ticket);
    if (!head) {
        head = tail = newNode;
        return;
    }
    if (strcmp(ticket, "FAST_TRACK") == 0) {
        struct Node* temp = head;
        while (temp && strcmp(temp->ticket, "FAST_TRACK") == 0)
            temp = temp->next;
        if (!temp) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            newNode->next = temp;
            newNode->prev = temp->prev;
            if (temp->prev) temp->prev->next = newNode;
            else head = newNode;
            temp->prev = newNode;
        }
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void dequeue() {
    for (int i = 0; i < 4 && head; i++) {
        struct Node* temp = head;
        printf("%s ", temp->name);
        head = head->next;
        if (head) head->prev = NULL;
        free(temp);
    }
    printf("got into the boat.\n");
}

void removeVisitor(int n) {
    for (int i = 0; i < n; i++) {
        char removeName[30];
        scanf("%s", removeName);
        struct Node* temp = head;
        while (temp) {
            if (strcmp(temp->name, removeName) == 0) {
                if (temp->prev) temp->prev->next = temp->next;
                else head = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                else tail = temp->prev;
                free(temp);
                break;
            }
            temp = temp->next;
        }
    }
}

void displayQueue() {
    if (!head) {
        printf("No Name Ticket\n");
        return;
    }
    struct Node* temp = head;
    int index = 1;
    while (temp) {
        printf("%d %s %s\n", index++, temp->name, temp->ticket);
        temp = temp->next;
    }
}

int main() {
    int choice, n;
    char name[30], ticket[15];
    do {
        printf("\nMenu:\n");
        printf("1. Register Visitors\n");
        printf("2. Call Visitors\n");
        printf("3. Remove Visitors\n");
        printf("4. Show Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of visitors: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter name and ticket type (FAST_TRACK/REGULER): ");
                    scanf("%s %s", name, ticket);
                    enqueue(name, ticket);
                }
                displayQueue();
                break;
            case 2:
                dequeue();
                displayQueue();
                break;
            case 3:
                printf("Enter number of visitors to remove: ");
                scanf("%d", &n);
                removeVisitor(n);
                displayQueue();
                break;
            case 4:
                displayQueue();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
