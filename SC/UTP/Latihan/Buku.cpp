#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define SIZE 100

struct book{
    char name[100];
    char LibraryId[100];
    char title[100];
    int duration;
    char borrowingId[6];
    struct book* next;
} *books[SIZE];

int toUpper(char x){
    return ('a' <= x && x <= 'z') ? (x - ('a' - 'A')) : x;
}

char* generateId(char* title){
    static char id[6];
    id[0] = toUpper(title[0]);
    id[1] = toUpper(title[1]);
    for(int i = 2; i < 5; i++){
        id[i] = (rand() % 10) + '0';
    }
    id[5] = '\0';
    return id;
}

int hash(char *borrowingId){
    int num = atoi(&borrowingId[2]);
    int squared = num * num;
    int middle = (squared / 100) % 100;
    return middle % SIZE;
}

struct book *newBook(char* name, char* LibraryId, char* title, int duration){
    struct book* curr = (struct book*)malloc(sizeof(struct book));
    strcpy(curr->name, name);
    strcpy(curr->LibraryId, LibraryId);
    strcpy(curr->title, title);
    curr->duration = duration;
    strcpy(curr->borrowingId, generateId(title));
    curr->next = NULL;
    return curr;
}

bool validname(char* name){
    int len = strlen(name);
    return (len >= 3 && len <= 30);
}

bool validLibrary(char* LibraryId){
    if(strncmp(LibraryId, "LIB-", 4) != 0) return false;
    for(int i = 4; i < 9; i++){
        if(!isdigit(LibraryId[i])) return false;
    }
    return (strlen(LibraryId) == 9);
}

bool validtitle(char* title){
    int len = strlen(title);
    if(len < 3 || len > 50){
    	return 0;	
	}
    
    if(!isupper(title[0])){
    	return 0;
	}
	
	for(int i = 1; i < len; i++){
		if(title[i] == ' ' && title[i+1] != '\0'){
			if(!isupper(title[i+1])){
				return 0;
			}
		}
	}
}

bool validduration(int duration){
    return (duration >= 1 && duration <= 30);
}

void createBook(){
    char name[100], LibraryId[100], title[100];
    int duration;
    do{
        printf("Enter your full name: ");
        scanf("%[^\n]", name); getchar();
    }while(!validname(name));
    
    do{
        printf("Enter your library ID (format: LIB-XXXXX): ");
        scanf("%s", LibraryId); getchar();
    }while(!validLibrary(LibraryId));
    
    do{
        printf("Enter the book title: ");
        scanf("%[^\n]", title); getchar();
    }while(!validtitle(title));
    
    do{
        printf("Enter borrowing duration (1-30 days): ");
        scanf("%d", &duration);
    }while(!validduration(duration));
    
    struct book* new_book = newBook(name, LibraryId, title, duration);
    int key = hash(new_book->borrowingId);
    new_book->next = books[key];
    books[key] = new_book;
    printf("Book Borrowed Successfully! Borrowing ID: %s\n", new_book->borrowingId);
}

void viewBook(){
    bool found = false;
    for(int i = 0; i < SIZE ; i++){
        struct book* curr = books[i];
        while(curr){
            printf("========================================\n");
            printf("          Borrowed Book List            \n");
            printf("========================================\n");
            printf("Borrowing ID  	: %s\n", curr->borrowingId);
            printf("Borrower Name 	: %s\n", curr->name);
            printf("Library ID    	: %s\n", curr->LibraryId);
            printf("Book Title    	: %s\n", curr->title);
            printf("Duration      	: %d days\n", curr->duration);
            printf("Stored at Index	: %d\n", i);
            printf("========================================\n");
            curr = curr->next;
            found = true;
        }
    }
    if (!found) printf("No Books Borrowed Yet\n");
}

bool pop(char* borrowingId){
    int key = hash(borrowingId);
    struct book* curr = books[key], *prev = NULL;
    while(curr){
        if(strcmp(curr->borrowingId, borrowingId) == 0){
            if(prev) prev->next = curr->next;
            else books[key] = curr->next;
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void returnBook(){
    viewBook();
    char borrowingId[6];
    printf("Enter Borrowing ID to return: ");
    scanf("%s", borrowingId); getchar();
    if(pop(borrowingId)){
        printf("--------------------------------------------\n");
        printf("        Book Returned Successfully         \n");
        printf("--------------------------------------------\n");
        printf("Borrowing ID: %s\n", borrowingId);
        printf("--------------------------------------------\n");
    }else{
        printf("Borrowing Book Not Found\n");
    }
}

int main(){
    srand(time(NULL));
    int input;
    do{
        puts("======================================");
        puts("        BOOKHAVEN LIBRARY MANAGEMENT    ");
        puts("======================================");
        puts("1. Borrow Book");
        puts("2. View Borrowed Book");
        puts("3. Return Book");
        puts("4. Exit");
        puts("======================================");
        printf(">> ");
        scanf("%d", &input);
        getchar();
        switch(input){
            case 1:
                createBook();
                break;
            case 2:
                viewBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                return 0;
        }
    }while(input != 4);
    return 0;
}

