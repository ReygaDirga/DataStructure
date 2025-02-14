#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int count = 100;
struct Pokemon{
    int ID;
    char Name[25];
    int Price;
    struct Pokemon *next;
} *head, *tail, *current;

void printList(struct Pokemon* head) {
    while (head != NULL) {
        printf("ID  : %d\n", head->ID);
        printf("Name : %s\n", head->Name);
        printf("Price : %d\n", head->Price);
        head = head->next;
        printf("---------------------------------\n");
    }
}

// void pushtail(char Name[]){
//     srand(time(NULL));
//     current = (struct Pokemon*)malloc(sizeof(struct Pokemon)); 
//     strcpy(current->Name, Name);
//     current->ID = count;
//     count++;
//     current->Price = rand() % 9000 + 1000;
//     current->next = NULL;
//     if(!head){
//         head = tail = current;
//     } else {
//         tail->next = current;
//         tail = current;
//     }
// }

void pushmid(char Name[]){
    srand(time(NULL));
    current = (struct Pokemon*)malloc(sizeof(struct Pokemon)); 
    strcpy(current->Name, Name);
    current->ID = count;
    count++;
    current->Price = rand() % 9000 + 1000;
    current->next = NULL;
    if(!head){
        head = tail = current;
    } else if(strcmp(Name, head->Name) < 0){ 
        current->next = head;
        head = current;
    } else if(strcmp(Name, tail->Name) > 0){
        tail->next = current;
        tail = current;
    } else {
        Pokemon *temp = head;
        while(strcmp(temp->next->Name, Name) < 0){
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

void popMid(char target[]){
    if(head == NULL){
        return;
    }
    if (strcmp(head->Name, target) == 0){
        struct Pokemon *temp = head;
        head = head->next;
        temp -> next = NULL;
        free(temp);
    } else {
        struct Pokemon *temp1 = head;
        struct Pokemon *temp2 = head->next;
        while(strcmp(temp2->Name, target) != 0){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }    
}

void BuyCard(){
    char temp[25];
    printf("Masukkin nama kartu : ");
    scanf("%[^\n]", temp);getchar();
    pushmid(temp);
    printf("%s telah diinput\n", temp);
    printf("---------------------------------\n");
}

void ShowCard(){
    printList(head);
}

void DeleteCard(){
    char temp[25];
    printf("Masukkin nama kartu yang mau diapus: ");
    scanf("%[^\n]", temp);getchar();
    popMid(temp);
    printf("%s dah di apus\n", temp);
    printf("---------------------------------\n");
}

void ChangeCard(){
    BuyCard();
    DeleteCard();
    ShowCard();
}

int main(){
    srand(time(NULL));
    int choice;
    char Nama[25];
    strcpy(Nama, "Vulpix");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Diglett");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Zubat");
    pushmid(Nama);
    srand(time(NULL));

    strcpy(Nama, "Nidoran");
    pushmid(Nama);
    
    do{
        puts("1. Buy");
        puts("2. View");
        puts("3. Change");
        puts("4. Delete");
        puts("5. Exit");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice){
        case 1:
            BuyCard();
            break;
        case 2:
            ShowCard();
            break;
        case 3:
            ChangeCard();
            break;
        case 4:
            DeleteCard();
            break;
        }
    } while (choice != 5);
    return 0;
}