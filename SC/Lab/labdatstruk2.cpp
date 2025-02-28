#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    int key;
    char name[50];
    struct data* next;
} *head, *tail;

struct data * createData(int key, char *name){
    struct data* newData = (struct data*)malloc(sizeof(struct data));
    newData->key = key;
    strcpy(newData->name, name);
    newData->next = NULL;

    return newData;
}

void pushHead(struct data* newData){
    if(head == NULL){
        head = tail = newData;
    }else{
        newData->next = head;
        head = newData;
    }
}

void pushTail(struct data* newData){
    if(head == NULL){
        head = tail = newData;
    }else{
        tail->next = newData;
        tail = newData;
    }
}

void pushMid(struct data* newData){
    if(head==NULL){
        pushHead(newData);
    }else if(head->key > newData->key){
        pushHead(newData);
    }else if(tail->key < newData->key){
        pushTail(newData);
    }else{
        struct data* curr = head;
        while(curr->next->key < newData->key){
            curr = curr->next;
        }
        newData->next=curr->next;
        curr->next = newData;
    }
}

void view(){
    struct data *curr = head;
    while(curr!=NULL){
        printf("%d - %s\n", curr->key, curr->name);
        curr= curr->next;
    }
    puts("");
}

struct data* search(char *name){
    if(head == NULL){
        return NULL;
    }
    struct data* curr = head;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void popHead(){
    if(head == NULL){
        return;
    }else if(head == tail){
        free(head);
        head = tail = NULL;
    }else{
        struct data* curr = head;
        head = curr->next;
        free(curr);
    }
}

void popTail(){
    if(head == NULL){
        return;
    }else if(head == tail){
        free(head);
        head = tail = NULL;
    }else{
        struct data* curr = head;
        while(curr->next != tail){
            curr = curr->next;
        }
        free(tail);
        tail = curr;
        tail->next = NULL;
    }
}

void popMid(int key){
    if(head == NULL){
        return;
    }else if(head->key == key){
        popHead();
    }else if(tail->key == key){
        popTail();
    }else{
        struct data* curr = head;
        while(curr->next != tail && curr->next->key < key){
            curr = curr->next;
        }
        if(curr->next->key == key){
            struct data* deleted = curr->next;
            curr->next = deleted->next;
            free(deleted);
        }
    }
}

int main(){
    pushMid(createData(4, "Budi"));
    pushMid(createData(7, "Agung"));
    pushMid(createData(2, "Leslie"));
    pushMid(createData(5, "Charlie"));
    
    view();

    popMid(5);
    view();

    // struct data* res = search("Budi");
    // if(res == NULL){
    //     puts("Not Found");
    // }else{
    //     printf("%s has key %d\n", res->name, res->key);
    // }
    return 0;
}