#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100

struct gadget{
	char name[100];
	char idPelanggan[100];
	char namaGadget[100];
	int jumlah;
	char idTransaksi[100];
	struct gadget* next;
}*gadgets[SIZE];

int toUpper(char x){
	return ('a' <= x && x <= 'z') ? (x - ('a' - 'A')) : x;
}

int hash(char* idTransaksi){
	int num = atoi(&idTransaksi[2]);
	int square = num * num;
	int middle = (square / 100) % 100;
	return middle % SIZE;
}

char* generate(char* namaGadget){
	static char id[6];
	id[0] = toUpper(namaGadget[0]);
	id[1] = toUpper(namaGadget[1]);
	for(int i = 2; i < 5; i++){
		id[i] = (rand()%10) + '0';
	}
	id[5] = '\0';
	return id;
}

struct gadget *newGadget(char* name, char* idPelanggan, char* namaGadget, int jumlah){
	struct gadget* curr = (struct gadget*)malloc(sizeof(struct gadget));
	strcpy(curr->name, name);
	strcpy(curr->idPelanggan, idPelanggan);
	strcpy(curr->namaGadget, namaGadget);
	curr->jumlah = jumlah;
	strcpy(curr->idTransaksi, generate(namaGadget));
	curr->next = NULL;
	return curr;
}

bool validname(char* name){
	int len = strlen(name);
	return (3<=len && len <=30);
}

bool validid(char* idPelanggan){
	if(strncmp(idPelanggan, "CUST-", 5) != 0) return false;
	for(int i = 5; i < 10; i++){
		if(!isdigit(idPelanggan[i])) return false;
	}
	return (strlen(idPelanggan) == 10);
}

bool validGadget(char* namaGadget){
	int len = strlen(namaGadget);
	return(3<= len && len <= 50);
}

bool validdur(int jumlah){
	return(jumlah >= 1 && jumlah <= 100);
}

void creatBuy(){
	char name[100];
	char idPelanggan[100];
	char namaGadget[100];
	int jumlah;
	
	do{
		printf("Masukkan nama anda : ");
		scanf("%[^\n]", name); getchar();
	}while(!validname(name));
	
	do{
		printf("Masukkan id Pelanggan [CUST-XXXX] : ");
		scanf("%[^\n]", idPelanggan); getchar();
	}while(!validid(idPelanggan));
	
	do{
		printf("Masukkan nama gadget yang ingin dibeli : ");
		scanf("%[^\n]", namaGadget); getchar();	
	}while(!validGadget(namaGadget));
	
	do{
		printf("Masukkan jumlah unit : ");
		scanf("%d", &jumlah); getchar();
	}while(!validdur(jumlah));
	
	struct gadget* curr = newGadget(name, idPelanggan, namaGadget, jumlah);
	int key = hash(curr->idTransaksi);
	curr->next = gadgets[key];
	gadgets[key] = curr;
	printf("data berhasil dibuat dengan id transaction : %s\n", curr->idTransaksi);
	
}

void showTransaction(){
	bool found = false;
	for(int i = 0; i < SIZE; i++){
		struct gadget* curr = gadgets[i];
		while(curr){
			printf("=========================");
			printf("Id Transaction : %s\n", curr->idTransaksi);
			printf("id Pelanggan   : %s\n", curr->idPelanggan);
			printf("Name           : %s\n", curr->name);
			printf("Nama Gadget    : %s\n", curr->namaGadget);
			printf("Jumlah         : %d\n", curr->jumlah);
			printf("Stored index   : %d\n", i);
			printf("=========================");
			curr = curr->next;
			found = true;
		}
	}
	if(!found){
		puts("data tidak ada");
	}
}

bool pop(char* idTransaction){
	int key = hash(idTransaction);
	struct gadget* curr = gadgets[key], *prev = NULL;
	if(strcmp(curr->idTransaksi, idTransaction) == 0){
		if(prev){
			prev->next = curr->next;
		}else{
			gadgets[key] = curr->next;
			free(curr);
			return true;
		}
	}
}

void cancelTransaction(){
	showTransaction();
	char id[10];
	printf("Masukkan id yang ingin dihapus : ");
	scanf("%[^\n]", id); getchar();
	if(pop(id)){
		printf("data dengan id transaction : %s\n", id);
	}else{
		puts("id tidak ada");
	}
}

int main(){
	srand(time(NULL));
	int input = -1;
	do{
		puts("======================");
		puts("Penjualan Gadget");
		puts("======================");
		puts("1. Beli Gadget");
		puts("2. Lihat transaksi");
		puts("3. Batalkan transaksi");
		puts("4. exit");
		printf(">> ");
		scanf("%d", &input); getchar();
		
		switch(input){
			case 1:
				creatBuy();
				break;
			case 2:
				showTransaction();
				break;
			case 3:
				cancelTransaction();
				break;
			case 4:
				return 0;
		}
	}while(input != 4);
	return 0;
}
