#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struktur node

struct Node{
    int id;
    char nama[50];
    struct Node* prev;
    struct Node* next;
} *head, *tail;

struct Node* createNewNode(int id, char nama[]){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->nama, nama);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void pushHead(int id, char nama[]){
    struct Node* newNode = createNewNode(id, nama);
    if(head ==  NULL){
        head = tail = newNode;
    }else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void pushTail(int id, char nama[]){
    struct Node* newNode = createNewNode(id, nama);
    if(head ==  NULL){
        head = tail = newNode;
    }else{
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void pushMid(int id, char nama[]){
    if(head == NULL){
        struct Node* newNode = createNewNode(id, nama);
        head = tail = newNode;
    }
    else if(id < head->id){
        pushHead(id, nama);
    }
    else if(id >= tail->id){
        pushTail(id, nama);
    }else{
        struct Node* newNode = createNewNode(id, nama);
        struct Node* curr = head;
        while(curr != NULL && curr->id <= newNode->id){
            curr = curr->next;
        }
        newNode->prev = curr->prev;
        newNode->next = curr;

        // newNode->prev->next = newNode;
        // curr->prev 
    }
}

struct Node* popHead(){
    if(head == NULL){
        return NULL;
    }
    else if(head == tail){
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }else{
        struct Node* temp =  head;
        head = head->next;
        return temp;
    }
}

struct Node* popTail(){
    if(head == NULL){
        return NULL;
    }
    else if(head == tail){
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }else{
        struct Node* temp =  head;
        head = head->next;
        return temp;
    }
}

struct Node* popMid(int id){
    if(head == NULL){
        return NULL;
    }else if(id == head->id){
        return popHead();
    }else if(id == tail->id){
        return popTail();
    }else{
        struct Node* curr = head;
        while(curr->id != id){
            curr = curr->next;
        }
        if(curr == NULL){
            return NULL;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        return curr;
    }
}

void forwardPrint(){
    struct Node* curr = head;
    while(curr != NULL){
        printf("%d %s <->", curr->id, curr->nama);
        curr = curr->next;
    }
    printf("NULL\n");
}

void backwardPrint(){
    struct Node* curr = tail;
    while(curr != NULL){
        printf("%d %s <->", curr->id, curr->nama);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main(){
    char tempp[50], temp1[50];
    strcpy(tempp, "Anid");
    strcpy(temp1, "Budi");
    pushHead(1, tempp);
    pushHead(2, temp1);

    // pushTail(1, temp);
    // pushTail(2, temp1);

    // forwardPrint();

    struct Node* temp = popHead();
    if(temp!=NULL){
        printf("Deleted %d %s\n", temp->id, temp->nama);
        free(temp);
    }else{
        printf("No data\n");
    }
    backwardPrint();
}