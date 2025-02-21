#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define HASH_SIZE 100
#define getch while(getchar() != '\n')

struct booking{
    char name[100];
    char phone[100];
    int age;
    char typeroom[100];
    int duration;
    char bookingid[100];
    struct booking* next;
}*bookings[HASH_SIZE];

int getHashKey(char *bookingid){
    int x = 0;
    for(int i = 2; i<5; i++){
        x+=bookingid[i] - '0';
    }
    return (x-1)%HASH_SIZE;
}

char toUpper(char x){
    return 'a' <= x && x <= 'z'? x - ('a' - 'A'): x;
}

char* generateID(char* typeroom){
    char* id = (char*)malloc(sizeof(char)*7);
    for(int i = 0; i<5; i++){
        id[i] = i < 2 ? toUpper(typeroom[i]): rand()%10+'0';
    }
    id[5] = '\0';
    return id;
}

struct booking* newBooking(char* name, char* phone, int age, char* typeroom, int duration){
    struct booking* curr = (struct booking*)malloc(sizeof(struct booking));
    strcpy(curr->name, name);
    strcpy(curr->phone, phone);
    curr->age = age;
    strcpy(curr->typeroom, typeroom);
    curr->duration = duration;
    strcpy(curr->bookingid, generateID(typeroom));
    curr->next = NULL;
    return curr;
}

void pushTail(struct booking* newData){
    int hash = getHashKey(newData->bookingid);

    if(bookings[hash] == NULL){
        bookings[hash] = newData;
        return;
    }else{
        struct booking* curr = bookings[hash];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newData;
    }
}

bool validFullName(char* name){
    int len = strlen(name);
    return 3 <= len && len <= 30;
}

bool validPhone(char* phone){
    if(phone[0] != '+' || phone[1] != '6' || phone[2] != '2'){
        return false;
    }
    int space = 0;
    int len = strlen(phone);
    for(int i = 3, len = strlen(phone); i<len; i++){
        if(phone[i] == ' '){
            space++;
        }
    }
    return space >= 1 && len - (space + 3) == 11;
}

bool validAge(int age){
    return age >= 18;
}

bool validRoom(char* typeroom){
    return strcmp(typeroom, "Reguler") == 0 || 
            strcmp(typeroom, "Deluxe") == 0 || 
            strcmp(typeroom, "Suite") == 0;
}

bool validDuration(int duration){
    return 1<= duration && duration <= 30;
}

void createBooking(){
    char name[100];
    char phone[100];
    int age;
    char typeroom[100];
    int duration;

    do
    {
        printf("Input Name: ");
        scanf("%[^\n]", name); getch;
    } while (!validFullName(name));
    do
    {
        printf("Input Phone: ");
        scanf("%[^\n]", phone); getch;
    } while (!validPhone(phone));
    do
    {
        printf("Input Age: ");
        scanf("%d", &age); getch;
    } while (!validAge(age));
    do
    {
        printf("Type Room : ");
        scanf("%[^\n]", typeroom); getch;
    } while (!validRoom(typeroom));
    do
    {
        printf("Duration : ");
        scanf("%d", &duration); getch;
    } while (!validDuration(duration));

    pushTail(newBooking(name, phone, age, typeroom, duration));
}

bool viewBooking(){
    bool found = false;
    for(int i = 0; i<HASH_SIZE; i++){
        struct booking* curr = bookings[i];
        while(curr){
            printf("====================================\n");
            printf("Name: %s\n", curr->name);
            printf("Phone: %s\n", curr->phone);
            printf("Age: %d\n", curr->age);
            printf("Type Room: %s\n", curr->typeroom);
            printf("Duration: %d hari\n", curr->duration);
            printf("Booking ID: %s\n", curr->bookingid);
            printf("====================================\n");
            printf("\n");
            curr = curr->next;
            found = true;
        }
    }
    return found;
}

bool pop(char* bookingid){
    int hash = getHashKey(bookingid);
    struct booking* curr = bookings[hash];
    while(curr){
        if(strcmp(curr->bookingid, bookingid) == 0){
            bookings[hash] = curr->next;
            free(curr);
        }else{
            while(curr->next){
                if(strcmp(curr->next->bookingid, bookingid) == 0){
                    struct booking* temp = curr->next;
                    curr->next = curr->next->next;
                    free(temp);
                    return true;

                }
                curr = curr->next;
            }
        }
        curr = curr->next;
    }
}

void deleteBooking(){
    if(!viewBooking()){
        return;
    }

    char bookingid[7];
    printf("Input booking id : ");
    scanf("%[^\n]", bookingid); getch;

    if(pop(bookingid)){
        printf("Deleted Booking %S\n", bookingid);
    }else{
        printf("ID Not Found\n");
    }

}

int main(){
    srand(time(NULL));
    int choice;
    do
    {
        printf("1. Create Booking\n");
        printf("2. View Booking\n");
        printf("3. Delete Booking\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice); getch;
        switch (choice)
        {
        case 1:
            createBooking();
            break;
        case 2:
            if(!viewBooking()){
                printf("No Booking Found\n");
            }
            break;
        case 3:
            deleteBooking();
            break;
        case 4:
            return 0;
        }
    } while (choice != 3);
    return 0;
}