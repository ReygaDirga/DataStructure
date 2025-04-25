// min heap = parent <= child
// max heap = parent >= child

// left child = 2 * n + 1
// right child = 2 * n + 2
// parent = (n - 1) / 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int heap_size = 0; // current size of the heap

int left(int n){
    return 2 * n + 1;
}
int right(int n){
    return 2 * n + 2;
}
int parent(int n){
    return (n - 1) / 2;
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(int val){
    if(heap_size == MAX_HEAP_SIZE){
        printf("Heap is full\n");
        return;
    }
    int n = heap_size++;
    heap[n] = val;
    while(n != 0 && heap[n] < heap[parent(n)]){
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}

void printHeapAsArray(){
    for(int i = 0; i<heap_size; i++){
        printf("%d -> ", heap[i]);
    }
    puts("");
}

void printHeapAsTree(int n, int depth){
    if(n >= heap_size) return;
    //Tranverse Right
    printHeapAsTree(right(n), depth + 1);
    for(int i = 0; i < depth; i++){
        printf("  ");
    }
    printf("%d\n", heap[n]);
    //Tranverse Left
    printHeapAsTree(left(n), depth + 1);

}

int popHead(){
    if(heap_size == 0){
        printf("Heap is empty\n");
        return -1;
    }
    int toPop = heap[0];
    heap[0] = heap[--heap_size];
    int n = 0;
    while(left(n) < heap_size){
        int t = left(n);
        if(right(n) < heap_size && heap[right(n)] < heap[t]){
            t = right(n);
        }
        if(heap[t] < heap[n]){
            swap(&heap[t], &heap[n]);
            n = t;
        }
        else{
            break;
        }
    }
    return toPop;
}

int main(){
    insertHeap(9);
    printHeapAsArray();
    insertHeap(19);
    printHeapAsArray();
    insertHeap(36);
    printHeapAsArray();
    insertHeap(8);
    printHeapAsArray();
    insertHeap(10);
    printHeapAsArray();
    insertHeap(12);
    printHeapAsArray();
    insertHeap(5);
    printHeapAsArray();

    puts("======================\n");
    printHeapAsTree(0,0);
    puts("======================\n");

    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    printf("You have pop: %d\n", popHead());
    printHeapAsArray();
    return 0;
}