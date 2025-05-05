#include <stdio.h>
#define MAX 100

typedef struct MinHeap {
    int size;
    int arr[MAX];
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void insert(MinHeap* heap, int value) {
    if (heap->size >= MAX) {
        printf("FULL\n");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    // Perbaiki posisi ke atas (UpHeap)
    while (i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[parent(i)]);
        i = parent(i);
    }
}

void downHeap(MinHeap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }

    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        downHeap(heap, smallest);
    }
}

int extract(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Empty\n");
        return -1;
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    downHeap(heap, 0);  // Lupa manggil ini, makanya heap rusak

    return root;
}

void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    MinHeap heap;
    heap.size = 0;

    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 20);
    insert(&heap, 3);

    printf("Heap sebelum extract:\n");
    printHeap(&heap);

    int extracted = extract(&heap);
    printf("Nilai di-extract: %d\n", extracted);

    printf("Heap setelah extract:\n");
    printHeap(&heap);

    return 0;
}
