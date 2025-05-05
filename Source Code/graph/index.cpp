#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// jumlah vertex = 5
#define MAX 5

void createMatrix(int matrix[][MAX], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matrix[i][j] = 0; // awalnya semua 0 karena tidak ada jalur
        }
    }
}

void printMatrix(int matrix[][MAX], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            printf("%d ", matrix[i][j]);
        }
        puts(" ");
    }
}

void addEdgeMatrix(int matrix[][MAX], int src, int dest){
    matrix[src][dest] = 1; // kalau punya jalur -> kita tandain 1
    matrix[dest][src] = 1; // jika graph tidak berarah
}

void bfsMatrix(int matrix[][MAX], int vertices, int startVertex){
    //Step 1: initialize visited array
    bool visited[vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = false; // semua vertex belum dikunjungi
    }

    //step 2: initialize queue
    int queue[100];
    int front = 0; // depan queue
    int rear = 0; // belakang queue

    visited[startVertex] = true; // kita tandain starting = true
    queue[rear++] = startVertex; // Masukkin ke dalam queue

    // kita pengen looping untuk BFS
    while(front < rear){ // selama masih ada node di dalam queue = gak bakal sama
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // kita pengen explore vertex tersebut punya neighbors
        for(int i = 0; i < vertices; i++){
            // untuk cek apakah ada edge     // biar gak visit node yang udah pernah
            if(matrix[currentVertex][i] == 1 && !visited[i]){
                visited[i] = true; // kita tandain true karena udah ke visit
                queue[rear++] = i; // kita tinggal masukkin ke dalam queue
            }
        } 
    }
    puts("");
}

void dfsMatrix(int matrix[][MAX], int vertices, int startVertex){
    //Step 1: initialize visited array
    bool visited[vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = false; // semua vertex belum dikunjungi
    }
    int stack[100], top = -1; // kalau stack empty -> top = -1
    stack[++top] = startVertex; // karena top nya di index 0
    while(top >= 0){
        int currentVertex = stack[top--];
        // kita visit kalau belom trus mark as true
        if(!visited[currentVertex]){
            printf("%d ", currentVertex);
            visited[currentVertex] = true; // kita tandain true karena udah ke visit
        }

        //visit semua neighbors dari paling besar ke terkecil ( karena stack )
        for(int i = vertices - 1; i >= 0; i--){
            if(matrix[currentVertex][i] == 1 && !visited[i]){
                stack[++top] = i;
            }
        }
    }
    puts("");
}

int main(){
    int vertices = MAX;

    int matrix[MAX][MAX];
    createMatrix(matrix, vertices);
    
    addEdgeMatrix(matrix, 0, 1); // menambah jalur dari vertex 0 ke vertex 1
    addEdgeMatrix(matrix, 0, 2); // menambah jalur dari vertex 0 ke vertex 2
    addEdgeMatrix(matrix, 1, 2); // menambah jalur dari vertex 1 ke vertex 2
    addEdgeMatrix(matrix, 1, 3); // menambah jalur dari vertex 1 ke vertex 3
    addEdgeMatrix(matrix, 2, 4); // menambah jalur dari vertex 2 ke vertex 4
    

    puts("Adjacency Matrix:");
    printMatrix(matrix, vertices);

    puts("\nBFS Matrix:");
    bfsMatrix(matrix, vertices, 0); // mulai dari vertex 0

    puts("\nDFS Matrix:");
    dfsMatrix(matrix, vertices, 0); // mulai dari vertex 0
    return 0;
}