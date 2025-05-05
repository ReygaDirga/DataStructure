#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 100

struct booking{
	char name[100];
	char phone[100];
	int age;
	char roomType[100];
	int duration;
	char bookingid[100];
	struct booking* next;
}*booking[SIZE];

int toUpper(char x){
	return 'a' <= x && x <= 'z'? x - ('a' - 'A'): x;
}

char* generateid(char* roomType){
	char* id = (char*)malloc(sizeof(char*)7);
	for(int i = 0; i<5; i++){
		id[i] = i < 2 ? toUpper(roomType[i]) : rand()%10 +'0';
	}
	id[5] = '\0'
	return id;
}

struct booking* newBooking(char* name, char* phone, int age, char* roomtype, int duration, char*bookingid){
	struct booking* curr = (struct booking*)malloc(sizeof(struct booking*));
	strcpy(curr->name, name);
	strcpy(curr->phone, phone);
	curr->age = age;
	strcpy(curr->roomType, roomtype);
	curr->duration = duration;
	strcpy(curr->bookingid, generateid(bookingid));
	return curr;
}

void pushtail(struct booking* newData){
	int hash = hash(newData->bookingid);
	if(booking[hash] == NULL){
		booking[hash] = newData;
		return;
	}else{
		struct booking* curr = booking[hash];
		while(curr->next){
			cur = curr->next;
		}
		curr->next = newData;
	}
}

void viewBooking(){
	bool found = false;
	for(int i = 0; i<SIZE; i++){
		struct booking* curr = booking[i];
		while(curr){
			printf("===============================================\n");
			printf("Booking id : %s\n", curr->bookingid);
			printf("Name : %s\n", curr->name);
			printf("Phone : %s\n", curr->phone);
			printf("Age : %s\n", curr->age);
			printf("Type Room : %s\n", curr->roomType);
			printf("Duration : %s\n", curr->duration);	
			printf("===============================================\n");
		}
	}
}

bool pop(char* bookingId){
	int hash = hash(bookingId);
	struct booking* del = booking[hash];
	while(del){
		if(strcmp(del->bookingid, bookingid)==0){
			booking[hash] = del->next;
			free(del)
		}else{
			while(del->next){
				if(strcmp(del->next->bookingid, bookingid) == 0){
					struct booking* temp = temp->next;
					temp->next = temp->next->next;
					free(temp);
					return true;
				}
			}
		}
	}
}

void deleteBooking(){
	if(!viewBooking){
		printf("Data tidak ada\n");
		return;
	}
	char bookingId[7];
	printf("Masukkan booking id yang mau dihapus : ");
	scanf("%[^\n]", bookingId); getchar();
	
	if(pop(bookingId)){
		printf("Delete booking id %s\n", bookingid);
	}else{
		printf("ID Not Found");
	}
	
}

int hash(char *bookingid){
	int x = 0;
	for(int i = 2; i<5; i++){
		x+=bookingid[i] -'0';
	}
	return (x-1)%SIZE;
}

bool validname(char* name){
	int l = strlen(name);
	return 3 <= l && l <= 30;
}

bool validphone(char* phone){
	if(phone[0] != '+' || phone[1] != '6' || phone[2] != '2'){
		return false;
	}
	int space = 0;
	int len = strlen(phone);
	for(int i = 3, len = strlen(phone); i < len; i++){
		if(phone[i] == ' '){
			space++
		}
	}
	return space >= 1 && len - (space + 3) == 11;
}

bool validage(int age){
	return age >= 18;
}

bool validroom(char* roomType){
	return strcmp(roomType, "Regular") == 0 || strcmp(roomType, "Deluxe") || strcmp(roomType, "Suite");
}

bool duration(int duration){
	return 1<= duration && duration <= 30;
}

void createBooking(){
	char name[100];
	char phone[100];
	int age;
	char roomType[100];
	int duration;
	
	do{
		printf("Masukkan nama anda : ");
		scanf("%[^\n]", name); getchar();
	}while(!validname(name));
	
	do{
		printf("Masukkan nomor telepon : ");
		scanf("%[^\n]", phone); getchar();
	}while(!validphone(phone));
	
	do{
		printf("Masukkan umur anda : ");
		scanf("%d", &age);
	}while(!validage(age));
	
	do{
		printf("Masukkan room type [Regular | Deluxe | Suite] : ");
		scanf("%[^\n]", roomType);
	}while(!validroom(roomType));
	
	do{
		printf("Masukkan durasi : ");
		scanf("%d", &duration)
	}while(!validduration(duration));
	
	pushtail(newBooking(name, phone, age, roomType, duration));
}

int main(){
	int input;
	do{
		puts("1. Create Booking");
		puts("2. View Booking");
		puts("3. Delete Booking");
		puts("4. Exit");
		printf(">> ");
		scanf("%d", input); getchar();
		switch(input){
			case 1:
				createBooking();
				break;
			case 2:
				if(!viewBooking){
					printf("Data tidak ada\n");
				}
				break;
			case 3:
				deleteBooking();
				break;
			case 4:
				return 0;
		}	
	}while(1);
	
	return 0;
}
