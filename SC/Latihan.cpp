#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
    int id;
    char name[30];
    int price;
}*h,*t,*c;

void trade();
void buy();
void sell();

int main(){
    int choice = -1;
    do
    {
        puts("1. Trade Card");
        puts("2. Buy Card");
        puts("3. Sell Card");
        puts("4. Exit");
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            trade();
            break;
        case 2:
            buy();
            break;
        case 3:
            sell();
            break;
        case 4:
            return 0;
        default:
            break;
        }
    } while (choice != 4);
    
    return 0;
}

void trade(){

}

void buy(int value){
    c = (struct data*)malloc(sizeof(struct data));
    c->name = value;
    c->next = NULL;
    if(!h){
        h=t=c;
    }else{
        t->next = c;
        t = c;
    }
}

void sell(){

}