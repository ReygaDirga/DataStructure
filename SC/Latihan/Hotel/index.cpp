#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASH_SIZE 100

struct Booking{
    char name[50];
    char phoneNum[20];
    int age;
    char roomType[20];
    int stayDuration;
    char bookingID[7];
    struct Booking *next;
} *bookings[HASH_SIZE];

Booking* createBooking(char* name, char* phoneNum, int age, char* roomType, int stayDuration){
    Booking* newBooking = (Booking*)malloc(sizeof(Booking));
    strcpy(newBooking->name, name);
    strcpy(newBooking->phoneNum, phoneNum);
    newBooking->age = age;
    strcpy(newBooking->roomType, roomType);
    newBooking->stayDuration = stayDuration;
    strcpy(newBooking->bookingID, generateID(roomType));
    newBooking->next = NULL;
    return newBooking;
}

void pushHead(Booking* c){
    int key = getHash(c->bookingID);
    if(bookings[key] == NULL){
        bookings[key] = c;
    }else{
        Booking* temp = bookings[key];
        while(temp != NULL && temp->next != NULL){
            temp = temp->next;
        }
        temp->next = c;
    }
}

void pop(char* id){
    int key = getHash(id);
    if(bookings[key] == NULL){
        return;
    }else if(strcmp(bookings[key]->bookingID, id) == 0){
        bookings[key] = NULL;
        return;
    }else{
        Booking* curr = bookings[key];
        while(curr->next != NULL && strcmp(curr->next->bookingID, id) != 0){
            curr = curr->next;
        }
        Booking* toPop = curr->next;
        curr->next = toPop->next;
        free(toPop);
        return;
    }
    puts("Booking not found!");
}

void view(){
    for (int i = 0; i < HASH_SIZE; i++)
    {
        if(bookings[i] == NULL) return;
        Booking* curr = bookings[i];
        while(curr != NULL){
            printf("Name : %s\n", curr->name);
            printf("Phone Number : %s\n", curr->phoneNum);
            printf("Age : %d\n", curr->age);
            printf("Room Type : %s\n", curr->roomType);
            printf("Stay Duration : %d\n", curr->stayDuration);
            printf("Booking ID : %s\n", curr->bookingID);
            puts("");
            curr = curr->next;
        }
    }
    
}

void enterr(){
    printf("Press enter to continue..."); getchar();
}

char* generateID(char* roomType){
    char* id = (char*)malloc(sizeof(7));
    sprintf(id, "%c%c%d%d%d", toupper(roomType[0]), toupper(roomType[1]), rand()%10, rand()%10, rand()%10);
    return id;
}

int getHash(char* id){
    int sumId = 1;
    for(int i = 2; i < 5; i++){
        sumId += id[i] - '0';
    }
    char string[100000];
    sprintf(string, "%d", sumId*=sumId);
    int l = strlen(string);
    int key = 0;
    if(l % 2==1){
        key = string[l/2] - '0';
    }else{
        char mid[3] = {string[l/2-1], string[l/2], '\0'};
        key = atoi(mid);
    }
    return key % HASH_SIZE;
}



void printMenu(){
    system("cls");
    puts("====================================");
    puts("=          HOTEL BOOKING           =");
    puts("====================================");
    puts("1. Booking");
    puts("2. View Booking");
    puts("3. Delete Booking");
    puts("4. Exit");
    puts("====================================");
}

int main(){
    srand(time(0));

    do
    {
        int inp = -1;
        printMenu();
        do
        {
            printf(">> ");
            scanf("%d", &inp); getchar();
        } while (inp < 1 || inp > 4);
        
    } while (1);
    
}