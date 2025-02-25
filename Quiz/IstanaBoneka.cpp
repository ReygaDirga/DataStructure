#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Data{
    char name[100];
    char ticket[100];
    struct Data *next;
    struct Data *prev;
}*h, *t, *c;

int queue = 0;

void display(){
    struct Data *temp = h;
    int i = 1;
    if(temp == NULL){
        printf("No data available\n");
        return;
    }
    while(temp != NULL){
        printf("%d %-10s %s\n", i, temp->name, temp->ticket);
        temp = temp->next;
        i++;
    }
}

void push(char name[], char ticket[]){
    c = (struct Data*)malloc(sizeof(struct Data));
    strcpy(c->name, name);
    strcpy(c->ticket, ticket);
    c->prev = NULL;
    c->next = NULL;
    if(h == NULL){
        h = t = c;
    }
    struct Data *temp = h;
    while(temp != NULL){
        int compareTick = strcmp(temp->ticket, c->ticket);

        if((compareTick > 0)){
            c->next = temp;
            c->prev = temp->prev;

            if(temp->prev != NULL){
                temp->prev->next = c;
            }else{
                h = c;
            }
            temp->prev = c;
            return;
        }
        temp = temp->next;
    }
    t->next = c;
    c->prev = t;
    t = c;
}

void popp(char name[]){
    if(h == NULL){
        return;
    }
    struct Data *temp = h;
    while(temp != NULL && strcmp(temp->name, name) != 0){
        temp = temp->next;
    }
    if(temp == NULL){
        return;
    }
    if(temp == h){
        h = h->next;
        if(h){
            h->prev = NULL;
        }
        free(temp);
    }else if(temp == t){
        t = t->prev;
        if(t){
            t->next = NULL;
        }
        free(temp);
    }else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}

void search(char name[]){
    struct Data *temp = h;
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            printf("%s %s\n", temp->name, temp->ticket);
            return;
        }
        temp = temp->next;
    }
    printf("Data not found\n");
}

void popHead(){
    if(h == NULL){
        return;
    }
    struct Data* temp = h;
    printf("%s", temp->name);
    h = h->next;
    h->prev = NULL;
    if(h != NULL){
        h->prev = NULL;
    }else{
        t = NULL;
    }
    free(temp);
}

int main(){

    int variabel;
    int n;
    while(1){
        if(queue == 0){
            printf("Queue is empty\n");
        } else {
            printf("Queue: %d\n", queue);
            display();
        }
        do{
            printf("1. Register\n");
            printf("2. Remove\n");
            printf("3. Call\n");
            printf("4. Exit\n");
            printf(">> ");
            scanf("%d", &variabel); getchar();
            switch (variabel)
            {
            case 1:
                scanf("%d", &n); getchar();
                for (int i = 0; i < n; i++)
                {
                    char name[20], ticket[20];
                    scanf("%s %s", name, ticket); getchar();
                    push(name, ticket);
                    queue++;
                }
                break;
            case 2:
                scanf("%d", &n); getchar();
                for (int i = 0; i < n; i++)
                {
                    char name[20];
                    scanf("%s", name); getchar();
                    popp(name);
                    queue--;
                }
                break;
            case 3:
                for (int i = 0; i < 4; i++)
                {
                    popHead();
                    if(queue == 0) break;
                    queue--;
                }
                puts("got into the boat");
                break;
            case 4:
                break;
            }
        }while(1);
    }
    return 0;
}