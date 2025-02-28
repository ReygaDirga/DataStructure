#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_KEY_LENGTH 50

typedef struct Node {
    char key[MAX_KEY_LENGTH];
    int value;
    struct Node* next;
} Node;

typedef struct {
    char key[MAX_KEY_LENGTH];
    int value;
    int occupied;
} HashTable_Linear[TABLE_SIZE];

typedef struct {
    Node* head;
} HashTable_Chaining[TABLE_SIZE];

int hash(const char* key) {
    int hash = 0;
    while (*key) {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

void insertLinear(HashTable_Linear table, const char* key, int value) {
    int index = hash(key);
    int start = index;
    while (table[index].occupied) {
        index = (index + 1) % TABLE_SIZE;
        if (index == start) {
            printf("Table penuh! Tidak bisa memasukkan %s\n", key);
            return;
        }
    }
    strcpy(table[index].key, key);
    table[index].value = value;
    table[index].occupied = 1;
}

void insertChaining(HashTable_Chaining table, const char* key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = table[index].head;
    table[index].head = newNode;
}

int searchLinear(HashTable_Linear table, const char* key) {
    int index = hash(key);
    int start = index;
    while (table[index].occupied) {
        if (strcmp(table[index].key, key) == 0)
            return table[index].value;
        index = (index + 1) % TABLE_SIZE;
        if (index == start)
            break;
    }
    return -1;
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

void displayLinear(HashTable_Linear table) {
    printf("Hash Table (Linear Probing):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].occupied)
            printf("[%d] Key: %s, Value: %d\n", i, table[i].key, table[i].value);
        else
            printf("[%d] EMPTY\n", i);
    }
}

void displayChaining(HashTable_Chaining table) {
    printf("Hash Table (Chaining):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] ", i);
        Node* curr = table[i].head;
        while (curr) {
            printf("-> (Key: %s, Value: %d) ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable_Linear tableLinear = {0};
    HashTable_Chaining tableChaining = {NULL};

    insertLinear(tableLinear, "apple", 100);
    insertLinear(tableLinear, "banana", 200);
    insertLinear(tableLinear, "cherry", 300);
    insertLinear(tableLinear, "date", 400);
    insertLinear(tableLinear, "elderberry", 500);

    insertChaining(tableChaining, "apple", 100);
    insertChaining(tableChaining, "apple", 200);
    insertChaining(tableChaining, "cherry", 300);
    insertChaining(tableChaining, "date", 400);
    insertChaining(tableChaining, "elderberry", 500);

    displayLinear(tableLinear);
    displayChaining(tableChaining);

    printf("\nSearch Key 'banana' in Linear: %d\n", searchLinear(tableLinear, "banana"));
    printf("Search Key 'banana' in Chaining: %d\n", searchChaining(tableChaining, "banana"));
    
    return 0;
}
