#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tnode{
    char name[30];
    char ticket[50];
    struct tnode *prev;
    struct tnode *next;
}*h, *t, *c;

tnode* createNode(char name[], char ticket[]){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->ticket, ticket);
    c->prev = NULL;
    c->next = NULL;
    return c;
}

void pushMid(char name[], char ticket[]){
    tnode* c = createNode(name, ticket);
    if(h == NULL){
        h = t = c;
    }else if(strcmp(c->ticket, "FAST_TRACK") == 0){
        c->next = h;
        h->prev = c;
        h = c;
    }else if(strcmp(c->ticket, "REGULER") == 0){
        c->prev = t;
        t->next = c;
        t = c;
    }else{
        struct tnode* temp = h;
        while(temp != NULL && (strcmp(temp->ticket, c->ticket) < 0 || (strcmp(temp->ticket, c->ticket) == 0 && strcmp(temp->name, c->name) < 0))){
            temp = temp->next;
        }
        if(temp == NULL){
            c->prev = t;
            t->next = c;
            t = c;
        }else{
            c->next = temp;
            c->prev = temp->prev;
            if(temp->prev != NULL){
                temp->prev->next = c;
            }else{
                h = c;
            }
            temp->prev = c;
        }
    }
}

void popHead(){
    if(h == NULL) return;
    struct tnode* temp = h;
    h = h->next;
    free(temp);
}

void addGuest(){
    char name[30], ticket[50];
    printf("Name : ");
    scanf("%[^\n]", name); getchar();
    printf("Ticket : ");
    scanf("%[^\n]", ticket); getchar();
    pushMid(name, ticket);
}

void perin(struct tnode* h){
    while(h != NULL){
        printf("Name : %s\n", h->name);
        printf("Ticket : %s\n", h->ticket);
        h = h->next;
        printf("---------------------------------\n");
    }
}

void show(){
    perin(h);
}

int main(){

    int choice, n;
    do
    {
        puts("1. Add Guest");
        puts("2. Show Guest");
        puts("3. Remove Guest");
        puts("4. Exit");
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
            case 1:
                addGuest();
                break;
            case 2:
                show();
                break;
            case 3:
                popHead();
                break;
            case 4:
                return 0;
                break;
        }
    } while(1);

    return 0;
}