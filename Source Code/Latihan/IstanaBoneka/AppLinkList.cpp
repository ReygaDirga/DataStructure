#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct tnode{
    char name[10];
    char ticket[10];
    struct tnode *prev;
    struct tnode *next;
} *h, *t, *c;

int queue = 0;

void displayQueue(){
    struct tnode *temp = h;
    int i = 1;
    if(temp==NULL){
        printf("Queue is empty\n");
        return;
    }
    while(temp){
        printf("%d %-10s %s\n", i, temp->name, temp->ticket);
        temp = temp->next;
        i++;
    }
}

void pushMid(char name[], char ticket[]) {
    c = (struct tnode *)malloc(sizeof(struct tnode));
    strcpy(c->name, name);
    strcpy(c->ticket, ticket);
    c->prev = NULL;
    c->next = NULL;
    if (h == NULL) {
        h = t = c;
        return;
    }
    struct tnode *temp = h;
    while (temp != NULL) {
        int ticketCompare = strcmp(temp->ticket, c->ticket);

        if ((ticketCompare > 0)) {
            c->next = temp;
            c->prev = temp->prev;

            if (temp->prev != NULL) {
                temp->prev->next = c;
            } else {
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

void popMiddle(char name[]) {
    if (h == NULL) return;

    struct tnode *temp = h;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) return;

    if (temp == h) {
        h = h->next;
        if (h) h->prev = NULL;
        free(temp);
    } else if (temp == t) {
        t = t->prev;
        if (t) t->next = NULL;
        free(temp);
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}

void popHead() {
    if (h == NULL) {
        return;
    }
    struct tnode *temp = h;
    printf("%s ", temp->name);
    h = h->next;
    h->prev = NULL;
    if (h != NULL) {
        h->prev = NULL;
    } else {
        t = NULL;
    }
    free(temp);
}


int main(){
    char REG_REM_CALL[20];
    int n;
    while(1){
        if(queue == 0){
            printf("Queue is empty\n");
        } else {
            printf("Queue: %d\n", queue);
            displayQueue();
        }
        while(1){
            printf("REGISTER/REMOVE/CALL/EXIT: ");
            scanf("%s", REG_REM_CALL); getchar();
            if(strcmp(REG_REM_CALL, "REGISTER") == 0 || strcmp(REG_REM_CALL, "REMOVE") == 0 || strcmp(REG_REM_CALL, "CALL") == 0 || strcmp(REG_REM_CALL, "EXIT") == 0){
                break;
            } else {
                printf("Invalid input\n");
            }
        }
        if(strcmp(REG_REM_CALL, "REGISTER") == 0) {
            scanf("%d", &n); getchar();
            for (int i = 0; i < n; i++)
            {
                char name[20], ticket[20];
                scanf("%s %s", name, ticket); getchar();
                pushMid(name, ticket);
                queue++;
            }
        } else if (strcmp(REG_REM_CALL, "REMOVE") == 0){
            scanf("%d", &n); getchar();
            for (int i = 0; i < n; i++)
            {
                char name[20];
                scanf("%s", name); getchar();
                popMiddle(name);
                queue--;
            }
        } else if(strcmp(REG_REM_CALL, "CALL") == 0){
            for (int i = 0; i < 4; i++)
            {
                popHead();
                if(queue == 0) break;
                queue--;
            }
            puts("got into the boat");
        } else if(strcmp(REG_REM_CALL, "EXIT") == 0){
            break;
        }
    }
}