#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Data{
    int id;
    bool impact;
    bool likelihood;
    struct Data *next; 
    struct Data *prev;
}*h, *t, *c;

struct DeletedData {
    int id;
    char classification[10];
};

struct DeletedData deletedList[10];
int deletedCount = 0;

struct Data *table[10] = {NULL};

int hashing(int id){
    return id % 10;
}

const char* comper(bool impact, bool likelihood){
    if(impact == 1 && likelihood == 1) return "Critical";
    if(impact == 1 && likelihood == 0) return "High";
    if(impact == 0 && likelihood == 1) return "Medium";
    if(impact == 0 && likelihood == 0) return "Low";
}

int comperr(bool impact, bool likelihood){
    if(impact == 1 && likelihood == 1) return 3; 
    if(impact == 1 && likelihood == 0) return 2;
    if(impact == 0 && likelihood == 1) return 1; 
    if(impact == 0 && likelihood == 0) return 0;
}

void display(){
    printf("Vulnerability Queue:\n");
    struct Data *temp = h;
    while(temp){
        printf("ID: %d - %s\n", temp->id, comper(temp->impact, temp->likelihood));
        temp = temp->next;
    }
}

void displayDeleted(){
    printf("\nProcessing vulnerabilities...\n");
    printf("\nStored Processed Vulnerabilities\n");
    for(int i = 0; i < deletedCount; i++){
        printf("Index %d -> ID: %d\n", hashing(deletedList[i].id),deletedList[i].id);
    }
}

void dekyu(){
    if(h == NULL){
        puts("NO DATA");
        return;
    }
    struct Data *temp = h;

    deletedList[deletedCount].id = temp->id;
    strcpy(deletedList[deletedCount].classification, comper(temp->impact, temp->likelihood));
    deletedCount++;

    if(h == t){
        h = t = NULL;
    }else{
        h = h->next;
        h->prev = NULL;
    }
    free(temp);
}

void pushmid(int id, bool impact, bool likelihood){
    struct Data *data = (struct Data*)malloc(sizeof(struct Data));
    data->id = id;
    data->impact = impact;
    data->likelihood = likelihood;
    data->next = NULL;
    data->prev = NULL;

    if (!h) { 
        h = t = data;
        return;
    }

    int newPriority = comperr(impact, likelihood);

    struct Data *temp = h;
    while (temp && comperr(temp->impact, temp->likelihood) >= newPriority) {
        temp = temp->next;
    }

    if (!temp) {
        t->next = data;
        data->prev = t;
        t = data;
    } else if (temp == h) {
        data->next = h;
        h->prev = data;
        h = data;
    } else { 
        data->next = temp;
        data->prev = temp->prev;
        temp->prev->next = data;
        temp->prev = data;
    }
}

int main(){

    pushmid(3001, 0, 0);
    pushmid(3002, 1, 1);
    pushmid(3003, 1, 0);
    pushmid(3004, 0, 1);
    pushmid(3005, 1, 1);

    display();
    dekyu();
    dekyu();
    display();

    displayDeleted();

    return 0;
}
