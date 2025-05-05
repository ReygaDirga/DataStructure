#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    char judul[50];
    // int no;
    struct Node *next;
    struct Node *prev;
} *h, *t, *c;

int count = 0;
int flag = -1;

void freeList() {
    struct Node *temp = h;
    while (temp) {
        struct Node *next = temp->next;
        free(temp);
        temp = next;
    }
    h = t = NULL;
}

void showList()
{
    if(count==0)
    {
        puts("No Songs Available. Press ENTER to continue...");
        getchar();
        return;
    }
    struct Node *temp = h;
    int i=1;
    while(temp!=NULL)
    {
        printf("No %d. || %s\n", i, temp->judul);
        temp = temp->next;
        i++;
    }
    printf("Press ENTER to continue..."); getchar();
}

void pushMiddle(char songName[])
{
    c = (struct Node *)malloc(sizeof(struct Node));
    strcpy(c->judul, songName);
    c->next = NULL;
    c->prev = NULL;
    count++;

    if (!h)
    {
        h = t = c; // If the list is empty, initialize it
    }
    else if (strcmp(songName, h->judul) < 0)
    {
        // Insert at the head
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if (strcmp(songName, t->judul) > 0)
    {
        // Insert at the tail
        t->next = c;
        c->prev = t;
        t = c;
    }
    else
    {
        // Insert in the middle
        struct Node *temp = h;
        while (temp->next && strcmp(temp->next->judul, songName) < 0)
        {
            temp = temp->next;
        }
        c->next = temp->next;
        if (temp->next)
        {
            temp->next->prev = c;
        }
        c->prev = temp;
        temp->next = c;
    }
}

void addSong()
{
    puts("=============");
    printf("Insert Song Name\n>> ");
    char song[50];
    scanf("%[^\n]", song); getchar();
    pushMiddle(song);
    puts("Song Added.");
    printf("Press ENTER to continue..."); getchar();

}

void playSong(){
    if(!h){
        puts("No Songs Available. Press ENTER to continue...");
        getchar();
        return;
    }
    struct Node *c = h;
    int choice, cuse, loopFlag = 0;
    do
    {
        printf("\nNow playing: %s\n", c->judul);
        if(loopFlag==0)
        {
        puts("1. Next");
        puts("2. Previous");
        puts("3. Enable Loop");
        puts("4. Exit");
        }
        else
        {
            puts("1. Disable Loop");
            puts("2. Exit");
        }
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            if(loopFlag==0){
                if(c->next != NULL){
                    c = c->next;
                }
            } else {
                loopFlag = 0;
            }
            break;
        case 2:
            if(loopFlag==0)
            {
                if(c->prev != NULL){
                    c = c->prev;
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


int main()
{
    int choice = -1;
    while(choice!=4)
    {
        system("cls");
        puts("Music App");
        puts("=============");
        puts("1. Show List");
        puts("2. Add Song");
        puts("3. Play");
        puts("4. Exit");
        printf("=============\n>> "); scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            showList();
            break;
        case 2:
            addSong();
            break;
        case 3:
            playSong();
            break;
        default:
            break;
        }
    }
    freeList();
}