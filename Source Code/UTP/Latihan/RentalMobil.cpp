#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SIZE 100

struct rental{
	char name[100];
	char idPelanggan[100];
	char carName[100];
	int duration;
	char idRental[100];
	struct rental* next;
}*sewa[SIZE];

int toUpper(char x){
	return ('a' <= x && x <= 'z') ? (x - ('a' - 'A')) : x;
}

char* generateid(char* carName){
	static char id[6];
	id[0] = toUpper(carName[0]);
	id[1] = toUpper(carName[1]);
	for(int i = 2; i < 5; i++){
		id[i] = (rand()%10) + '0';
	}
	id[5] = '\0';
	return id;
}

struct rental *newRental(char* name, char* idPelanggan, char* carName, int duration){
	struct rental* curr = (struct rental*)malloc(sizeof(struct rental));
	strcpy(curr->name, name);
	strcpy(curr->idPelanggan, idPelanggan);
	strcpy(curr->carName, carName);
	curr->duration = duration;
	strcpy(curr->idRental, generateid(carName));
	curr->next = NULL;
	return curr;
}

int hash(char* idRental){
	int num = atoi(&idRental[2]);
	int square = num * num;
	int middle = (square / 100) % 100;
	return middle % SIZE;
}

bool validname(char* name){
	int len = strlen(name);
	return (3 <= len && len <= 30);
}

bool validID(char* idPelanggan){
	if(strncmp(idPelanggan, "CUST-", 5) != 0) return false;
	for(int i = 5; i < 10; i++){
		if(!isdigit(idPelanggan[i])) return false;
	}
	return(strlen(idPelanggan) == 10);
}

bool validcar(char* carName){
	int len = strlen(carName);
	return(3<= len && len <= 50);
}

bool validDur(int duration){
	return(duration >= 1 && duration <= 30);
}

void sewaMobil(){
	char name[100];
	char idPelanggan[100];
	char carName[100];
	int duration;
	char idRental[100];
	
	do{
		printf("Masukkan nama anda : ");
		scanf("%[^\n]", name); getchar();
	}while(!validname(name)); 
	
	do{
		printf("Masukkan Id Pelanggan [CUST-XXXXX] : ");
		scanf("%[^\n]", idPelanggan); getchar();
	}while(!validID(idPelanggan));
	
	do{
		printf("Masukkan nama kendaraan : ");
		scanf("%[^\n]", carName); getchar();
	}while(!validcar(carName));
	
	do{
		printf("Masukkan durasi sewa (1-30 days) : ");
		scanf("%d", &duration); getchar();
	}while(!validDur(duration));
	
	struct rental* curr = newRental(name, idPelanggan, carName, duration);
	int key = hash(curr->idRental);
	curr->next = sewa[key];
	sewa[key] = curr;
	printf("Berhasil input dengan Id Rental : %s\n", curr->idRental);
}

void showMobil(){
	bool found = false;
	for(int i = 0; i < SIZE; i++){
		struct rental* curr = sewa[i];
		while(curr){
			puts("==========================================");
			puts("	Manajemen Rental Mobil			");
			puts("==========================================");
			printf("ID Rental 		: %s\n", curr->idRental);
			printf("ID Pelanggan 	: %s\n", curr->idPelanggan);
			printf("Nama Pelanggan	: %s\n", curr->name);
			printf("Kendaraan		: %s\n", curr->carName);
			printf("Duration		: %d\n", curr->duration);
			printf("Stored index	: %d\n", i);
			puts("==========================================");
			curr = curr->next;
			found = true;
		}
	}
	if(!found){
		puts("Gak ada mobil yang di sewa");
	}
}

bool pop(char* idRental){
	int key = hash(idRental);
	struct rental* curr = sewa[key], *prev = NULL;
	while(curr){
		if(strcmp(curr->idRental, idRental) == 0){
			if(prev){
				prev->next = curr->next;
			}else{
				sewa[key] = curr->next;
				free(curr);
				return true;
			}
		}
	}
	return false;
}

void returnCar(){
	showMobil();
	char idrent[10];
	printf("Masukkan Id Rental yang ingin di hapus : ");
	scanf("%[^\n]", idrent); getchar();
	if(pop(idrent)){
		puts("==========================================");
		puts("	Berhasil Di Hapus			");
		puts("==========================================");
		printf("ID Rental  		: %s\n", idrent);
		puts("==========================================");
	}else{
		puts("ID tidak ditemukan");
	}
}

int main(){
	srand(time(NULL));
	int input = -1;
	do{
		puts("==========================================");
		puts("	Manajemen Rental Mobil			");
		puts("==========================================");
		puts("1. Rental Mobil");
		puts("2. Show Mobil");
		puts("3. Kembalikan Mobil");
		puts("4. Exit");
		puts("==========================================");
		printf(">> ");
		scanf("%d", &input); getchar();
		switch(input){
			case 1:
				sewaMobil();
				break;
			case 2:
				showMobil();
				break;
			case 3:
				returnCar();
				break;
			case 4:
				return 0;
		}
	}while(input != 4);
		
	return 0;
}
