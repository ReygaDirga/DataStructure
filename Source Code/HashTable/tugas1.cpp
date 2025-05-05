#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char nama[50];
    char telp[50];
    char email[50];
    struct Node *next;
} Node;

typedef struct {
    Node* head;
} HashTable_Chaining[TABLE_SIZE];

int hash(const char* key) {
    int sum = 0;
    while (*key) {
        sum += *key;
        key++;
    }
    int squared = sum * sum;

    int mid_digits;
    if (squared < 100) {
        mid_digits = squared % 10; 
    } else {
        mid_digits = (squared / 10) % 100;
    }
    return mid_digits % TABLE_SIZE;
}

void insertChaining(HashTable_Chaining table, const char* key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = table[index].head;
    table[index].head = newNode;
}

int searchChaining(HashTable_Chaining table, const char* key) {
    int index = hash(key);
    Node* curr = table[index].head;
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return -1;
}

void displayChaining(HashTable_Chaining table) {
    printf("Hash Table (Chaining with Mid Square Hashing):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node *temp = table[i].head;
        if (!temp) {
            printf("NULL\n");
            continue;
        }
        while (temp) {
            printf("[%s, %s, %s] -> ", temp->nama, temp->telp, temp->email);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    HashTable_Chaining tableChaining = {NULL};

    insertChaining(tableChaining, "apple", 100);
    insertChaining(tableChaining, "banana", 200);
    insertChaining(tableChaining, "cherry", 300);
    insertChaining(tableChaining, "date", 400);
    insertChaining(tableChaining, "elderberry", 500);

    displayChaining(tableChaining);

    printf("\nSearch Key 'banana': %d\n", searchChaining(tableChaining, "banana"));
    printf("Search Key 'grape': %d\n", searchChaining(tableChaining, "grape"));
    
    return 0;
}
