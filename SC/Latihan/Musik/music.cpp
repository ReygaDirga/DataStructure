#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct musik{
    int number;
    char judul[50];
    struct musik *prev;
    struct musik *next;
} *h, *t, *c;

int count = 0;

void perint(struct musik* h){
    while(h != NULL){
        printf("Nomor : %d\n", h->number);
        printf("Judul : %s\n", h->judul);
        h = h->next;
        printf("---------------------------------\n");
    }
}


void pushmid(char title[]){
    c = (struct musik*)malloc(sizeof(struct musik));
    count++;
    c->number = count;
    strcpy(c->judul, title);
    c->prev =NULL;
    c->next =NULL;

    if(!h){
        h = t = c;
    }else if(strcmp(title, h->judul) < 0){
        c->next = h;
        h->prev = c;
        h = c;
    }else if(strcmp(title, t->judul) > 0){
        c->prev = t;
        t->next = c;
        t = c;
    }else{
        musik *temp = h;
        while (strcmp(temp->next->judul, title) < 0)
        {
            temp = temp->next;
        }
        c->next = temp->next;
        c->prev = temp;
        if (temp->next) {
            temp->next->prev = c;
        }
        temp->next = c;
        
    }
}

void nambah(){
    char temp[25];
    printf("Masukkin judul lagu : ");
    scanf("%[^\n]", temp); getchar();
    pushmid(temp);
    puts("Data telah diinput");
}

void showmusic(){
    perint(h);
}

void playMusic(){
    if(!h){
        puts("Daftar lagu tidak ada");
        return;
    }
    struct musik *current = h;
    int choice, cuse;
    do
    {
        do
        {
            printf("\nNow playing: %s (Nomor: %d)\n", current->judul, current->number);
            printf("Looping [1/0] : ");
            printf(">> ");
            scanf("%d", &cuse);
        } while (cuse != 0);
        
        puts("1. Next");
        puts("2. Previous");
        puts("3. exit play mode");
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            if(current->next != NULL){
                current = current->next;
            }
            break;
        case 2:
            if(current->prev != NULL){
                current = current->prev;
            }
            break;
        case 3:
            break;
        }
    } while (choice != 3);
    
}

int main(){
    showmusic();
    int choice;
    do
    {
        puts("1. Add lagu");
        puts("2. tampilkan lagu");
        puts("3. play lagu");
        puts("4. exit");
        printf("Mau yang mana : ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            nambah();
            break;
        case 2:
            showmusic();
            break;
        case 3:
            playMusic();
            break;
        case 4:
            return 0;
        }
    } while (choice != 3);
    
}