#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    char nama[100];
    int laba_bersih;
    int hpp;
    int laba_kotor;
} UMKM;

typedef struct {
    int size;
    UMKM arr[MAX];
} MaxHeap;

void swap(UMKM* a, UMKM* b) {
    UMKM temp = *a;
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

void insert(MaxHeap* heap, char nama[], int laba_kotor, int hpp) {
    if (heap->size >= MAX) {
        printf("Heap penuh\n");
        return;
    }

    UMKM baru;
    strcpy(baru.nama, nama);
    baru.laba_kotor = laba_kotor;
    baru.hpp = hpp;
    baru.laba_bersih = baru.laba_kotor - hpp;

    int i = heap->size;
    heap->arr[i] = baru;
    heap->size++;

    // Debug: Print setelah insert data baru
    printf("Inserted: %s with laba_bersih: %d\n", baru.nama, baru.laba_bersih);

    while (i != 0 && heap->arr[parent(i)].laba_bersih < heap->arr[i].laba_bersih) {
        swap(&heap->arr[i], &heap->arr[parent(i)]);
        i = parent(i);
    }
}

void downHeap(MaxHeap* heap, int i) {
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->arr[left].laba_bersih > heap->arr[largest].laba_bersih)
        largest = left;
    if (right < heap->size && heap->arr[right].laba_bersih > heap->arr[largest].laba_bersih)
        largest = right;

    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);

        // Debug: Print setelah swap
        printf("DownHeap: Swap %s with %s\n", heap->arr[i].nama, heap->arr[largest].nama);
        downHeap(heap, largest);
    }
}

UMKM extract(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("empty\n");
        UMKM kosong = {"-", 0, 0, 0};
        return kosong;
    }

    UMKM root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    downHeap(heap, 0);

    return root;
}

void printHeap(MaxHeap* heap) {
    printf("Daftar UMKM: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%s (%d) ", heap->arr[i].nama, heap->arr[i].laba_bersih);
    }
    printf("\n");
}

int main() {
    MaxHeap heap;
    heap.size = 0;

    insert(&heap, "Cilokal", 1000, 250);
    insert(&heap, "Eserut", 500, 100);
    insert(&heap, "SotoMadura", 700, 300);
    insert(&heap, "BebekBarokah", 750, 50);
    insert(&heap, "Pijahat", 1800, 1100);
    insert(&heap, "Kaepce", 800, 30);
    insert(&heap, "soBakso", 300, 50);
    insert(&heap, "ayamMoza", 2000, 200);
    insert(&heap, "CirengHot", 1200, 400);

    printHeap(&heap);
    printf("Prioritas : %s\n", heap.arr[0].nama);

    return 0;
}
