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

void assignNum()
{
    struct musik *temp = h;
    int i = 1;
    while(temp!=NULL)
    {
        temp->number = i;
        temp = temp->next;
        i++;
    }
}

void pushmid(char title[]) {
    c = (struct musik *)malloc(sizeof(struct musik));
    strcpy(c->judul, title);
    c->prev = NULL;
    c->next = NULL;

    if (!h) {
        h = t = c;
    } else if (strcmp(title, h->judul) < 0) {
        c->next = h;
        h->prev = c;
        h = c;
    } else if (strcmp(title, t->judul) > 0) { 
        c->prev = t;
        t->next = c;
        t = c;
    } else { 
        struct musik *temp = h;
        while (temp->next != NULL && strcmp(temp->next->judul, title) < 0) {
            temp = temp->next;
        }
        c->next = temp->next;
        c->prev = temp;
        if (temp->next != NULL) {
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
    assignNum();
    puts("Data telah diinput");
}

void showmusic(){
    perint(h);
}

void playMusic(){
    if(!h){
        return;
    }
    int coos;
    puts("Play loop");
    puts("Play once");
    printf(">> ");
    scanf("%d", &coos);
    struct musik *c = h;
    int choice, cuse, loopFlag = 0;
    do
    {
        printf("\nNow playing: %s\n", c->judul);
        if(loopFlag==0)
        {
        puts("1. Next");
        puts("2. Previous");
        puts("3. Play Once");
        puts("4. Exit");
        }
        else
        {
            puts("1. Disable Loop");
            puts("2. Exit");
            puts("3. Looping again");
        }
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
        if(coos == 2){
            if(c->next != NULL){
                c = c->next;
            }else{
                return;
            }
        }
            if(loopFlag==0){
                if(c->next != NULL){
                    c = c->next;
                }else{
                    c = h;
                }
            } else {
                loopFlag = 0;
            }
            break;
        case 2:
        if(coos == 2){
            if(c->prev != NULL){
                c = c->prev;
            }
        }
            if(loopFlag==0)
            {
                if(c->prev != NULL){
                    c = c->prev;
                }else{
                    c = t;
                }
            } else {
                return;
            }
            break;
        case 3:
            if(loopFlag==0)
            {
                loopFlag=1;
            }
            break;
        case 4:
            if(loopFlag==0) return;
            break;
        }
    } while(1);
    
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