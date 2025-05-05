#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 50

struct Data{
    char coin[5];
    double price;
    Data *next;
} *arr[SIZE];

int midSquare(char coin[]){
    int hash = 0;
    int len = strlen(coin);
    int mid = len / 2;
    char mid_char[2] = {coin[mid], '\0'};
    int mid_val = atoi(mid_char);
    hash = mid_val * mid_val;
    return hash % SIZE;
}

void insert(char coin[], double price){
    Data *data = (Data*)malloc(sizeof(Data));
    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;

    int index = midSquare(coin);
    if(arr[index] == NULL){
        arr[index] = data;
    }else{
        struct Data *temp = arr[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
    }
}

void display(){
    for(int i = 0; i < SIZE; i++){
        if(arr[i] != NULL){
            struct Data *temp = arr[i];
            while(temp != NULL){
                printf("Coin: %s, Price: %.2f\n", temp->coin, temp->price);
                temp = temp->next;
            }
        }
    }
}


int main(){
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SQL", 172.59);
    insert("XRP", 2.57);

    display();
    return 0;
}