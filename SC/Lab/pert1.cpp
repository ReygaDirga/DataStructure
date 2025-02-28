#include <stdio.h>
#include <stdlib.h>

// Pointer = Variable yang menyimpan / menunjuk memory address
// malloc = 

struct Student{
    int age;
    int height;
} arrStudent[5];

int main(){

    Student student;

    student.age = 20;
    student.height = 170;

    //alokasi memory untuk struct
    struct Student* ptr2 = (Student*)malloc(sizeof(struct Student));

    //akses anggota dari struct pointer
    ptr2->age = 21;
    ptr2->height = 175;

    printf("age : %d, height : %d\n", ptr2->age, ptr2->height);

    free(ptr2);

    // akses anggota dari array of struct
    arrStudent[0].age = 12;
    arrStudent[1].age = 13;







    // int a = 10;
    // int *ptr = &a;

    // printf("memory dari ptr : %d\n", &ptr);
    // printf("value dari ptr : %d\n", ptr);
    // printf("value dari memory yang disimpan : %d\n", *ptr);

    // *ptr = 20;
    // printf("nilai a sekarang : %d\n", a);
    // malloc(sizeof(int));
    
    // int* ptr = (int *)malloc(sizeof(int));
    // *ptr = 20;
    // printf("alamat baru : %d, value dari alamat %d\n", ptr, *ptr);
}