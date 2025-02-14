#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// typedef struct {
//     char nim[10];
//     char nama[50];

// } mahasiswa;

struct mahasiswa{
    char nim[10];
    char nama[50];
};

int main(){

    // mahasiswa ppti21[100];
    // strcpy(ppti21[0].nim, "28897347632");
    // printf("%s\n", ppti21[0].nim);

    struct mahasiswa* ppti = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));

    return 0;

}