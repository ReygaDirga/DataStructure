#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct rumahsakit {
    char nama[20];
    int umur;
    int status;
    struct rumahsakit *next;
    struct rumahsakit *prev;
} *h, *t, *c;

void dekyu(){
    if(h == NULL){
        puts("gak ada data");
    }
    struct rumahsakit *temp = h;
    if(h == t){
        h = t = NULL;
    }else{
        h = h->next;
        h->prev = NULL;
    }
    free(temp);
    puts("Berhasil nambahin");
}

void ngeprint(struct rumahsakit* h) {
    while (h != NULL) {
        printf("Nama : %s || Umur : %d || Status : %d\n", h->nama, h->umur, h->status);
        h = h->next;
    }
}

void viewpasien() {
    if (!h) {
        puts("Belum ada pasien.");
    } else {
        ngeprint(h);
    }
}

void pushmid(char nama[], int umur, int status) {
    c = (struct rumahsakit *)malloc(sizeof(struct rumahsakit));
    strcpy(c->nama, nama);
    c->umur = umur;
    c->status = status;
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else if (c->status < h->status) { 
        c->next = h;
        h->prev = c;
        h = c;
    } else if (c->status >= t->status) { 
        c->prev = t;
        t->next = c;
        t = c;
    } else {
        struct rumahsakit *temp = h;
        while (temp && temp->status <= c->status) {
            temp = temp->next;
        }

        c->next = temp;
        c->prev = temp->prev;
        temp->prev->next = c;
        temp->prev = c;
    }
}

void nambah() {
    char temp[25];
    int umur, status;
    printf("Masukkin nama pasien : ");
    scanf("%[^\n]", temp); getchar();
    printf("Masukkin umur pasien : ");
    scanf("%d", &umur); getchar();
    puts("Masukkin status pasien : ");
    printf("1. Pertolongan cepat\n");
    printf("2. Tindakan rawat jalan\n");
    printf("3. Medical Check up\n");
    printf(">> ");
    scanf("%d", &status); getchar();
    pushmid(temp, umur, status);
    puts("Data telah diinput");
}

int main() {
    int choice;
    do {
        puts("1. Add pasien");
        puts("2. View pasien");
        puts("3. Dequeue");
        puts("4. Exit");
        printf("Mau yang mana : ");
        scanf("%d", &choice); getchar();
        switch (choice) {
        case 1:
            nambah();
            break;
        case 2:
            viewpasien();
            break;
        case 3:
            dekyu();
            break;
        }
    } while (choice != 4);

    return 0;
}
