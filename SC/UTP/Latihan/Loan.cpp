#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SIZE 100

struct loan{
	char name[100];
	char idPeminjam[100];
	char namaAlat[100];
	int duration;
	char IdLoan[100];
	struct loan* next;
}*loans[SIZE];

int toUpper(char x){
	return ('a' <= x && x <= 'z') ? (x - ('a' - 'A')): x ;
}

int hash(char* idLoan){
	int num = atoi(&idLoan[2]);
	int square = num * num;
	int middle = (square / 100) % 100;
	return middle % SIZE;
}

char* generateid(char* namaAlat){
	static char id[6];
	id[0] = toUpper(namaAlat[0]);
	id[1] = toUpper(namaAlat[1]);
	for(int i = 2; i < 5; i++){
		id[i] = (rand()%10) + '0';
	}
	id[5] = '\0';
	return id;
}

struct loan* newLoan(char* name, char* idPeminjam, char* namaAlat, int duration){
	struct loan* curr = (struct loan*)malloc(sizeof(struct loan));
	strcpy(curr->name, name);
	strcpy(curr->idPeminjam, idPeminjam);
	strcpy(curr->namaAlat, namaAlat);
	curr->duration = duration;
	strcpy(curr->IdLoan, generateid(namaAlat));
	curr->next = NULL;
	return curr;
}

bool validname(char* name){
	int len = strlen(name);
	return ( 3 <= len && len <= 30);
}

bool validid(char *idPeminjam){
	if(strncmp(idPeminjam, "USER-", 5)!=0) return false;
	for(int i = 5; i < 10; i++){
		if(!isdigit(idPeminjam[i]))return false;
	}
	return (strlen(idPeminjam) == 10);
}

bool namaAlatval(char* namaAlat){
	int len = strlen(namaAlat);
	return(5<=len && len <= 30);
}

bool valduration(int duration){
	return (duration >= 1 && duration <= 30);
}

void createLoan(){
	char name[100];
	char idPeminjam[100];
	char namaAlat[100];
	int duration;
	char IdLoan[100];
	
	do{
		printf("Masukkan nama anda : ");
		scanf("%[^\n]", name); getchar();
	}while(!validname(name));
	
	do{
		printf("Masukkan id Peminjam anda [USER-XXXXX] : ");
		scanf("%[^\n]", idPeminjam); getchar();
	}while(!validid(idPeminjam));
	
	do{
		printf("Masukkan nama alat yang ingin dipinjam : ");
		scanf("%[^\n]", namaAlat); getchar();
	}while(!namaAlatval(namaAlat));
	
	do{
		printf("Masukkan durasi peminjaman : ");
		scanf("%d", &duration); getchar();
	}while(!valduration(duration));
	
	struct loan* curr = newLoan(name, idPeminjam, namaAlat, duration);
	int key = hash(curr->IdLoan);
	curr->next = loans[key];
	loans[key] = curr;
	printf("Berhasil menambahkan dengan id Loan : %s\n", curr->IdLoan);
}

void showLoan(){
	bool found = false;
	for(int i = 0; i < SIZE; i++){
		struct loan* curr = loans[i];
		while(curr){
			printf("===========================\n");
			printf("Id Loan		: %s\n", curr->IdLoan);
			printf("Id Peminjam : %s\n", curr->idPeminjam);
			printf("name		: %s\n", curr->name);
			printf("nama alat	: %s\n", curr->namaAlat);
			printf("durasi		: %d\n", curr->duration);
			printf("stored index: %d\n", i);
			printf("============================\n");
			curr = curr->next;
			found = true;
		}
	}
	if(!found){
		puts("data tidak ada");
	}
}

bool pop(char* idLoan){
	int key = hash(idLoan);
	struct loan* curr = loans[key], *prev = NULL;
	while(curr){
		if(strcmp(curr->IdLoan, idLoan) == 0){
			if(prev){
				prev->next = curr->next;
			}else{
				loans[key] = curr->next;
				free(curr);
				return true;
			}
		}
	}
}

void returnLoan(){
	showLoan();
	char id[10];
	printf("Masukkan id Loan yang ingin dihapus : ");
	scanf("%[^\n]", id); getchar();
	if(pop(id)){
		printf("berhasil menghapus id loan : %s\n", id);
	}else{
		puts("id tidak ditemukan");
	}
}

int main(){
	srand(time(NULL));
	int input = -1;
	do{
		puts("=============================");
		puts("Peminjaman Barang");
		puts("=============================");
		puts("1. Pinjam barang");
		puts("2. Perlihatkan barang pinjam");
		puts("3. Kembalikan barang pinjaman");
		puts("4. exit");
		puts("=============================");
		printf(">> ");
		scanf("%d", &input); getchar();
		switch(input){
			case 1:
				createLoan();
				break;
			case 2:
				showLoan();
				break;
			case 3:
				returnLoan();
				break;
			case 4:
				return 0;
		}
	}while(input != 4);
	
	
	return 0;
}
