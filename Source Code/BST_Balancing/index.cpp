// AVL Tree -> Self Balancing Binary Search Tree
// insert dan update

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Mahasiswa{
    int age;
    char name[255];
    Mahasiswa *left, *right;
    int height;
};

Mahasiswa *createNewMhs(int age, char* name){
    Mahasiswa *newMhs = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    newMhs->age = age;
    strcpy(newMhs->name, name);
    newMhs->left = newMhs->right = NULL;
    newMhs->height = 1;
    return newMhs;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(Mahasiswa *curr){
    if(curr == NULL){
        return 0;
    }else{
        return curr->height;
    }
}

int getBalance(Mahasiswa *curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

Mahasiswa *rightRotate(Mahasiswa *curr){
    Mahasiswa *currLeft = curr->left;
    Mahasiswa *currLeftRight = currLeft->right;

    curr->left->right = curr;
    curr->left = currLeftRight;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));

    return currLeft;
}
Mahasiswa *leftRotate(Mahasiswa *curr){
    Mahasiswa *currRight = curr->right;
    Mahasiswa *currRightLeft = curr->right->left; // /currRight->left

    curr->right->left = curr;
    curr->right = currRightLeft;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));

    return currRight;
}

Mahasiswa *insertAVL(Mahasiswa *curr, int age, char name[100]){
    //kosong
    if(curr == NULL){
        return createNewMhs(age, name);
    }
    if(age < curr->age){
        curr->left = insertAVL(curr->left, age, name);
    }else if(age > curr->age){
        curr->right = insertAVL(curr->right, age, name);
    }
    // update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    // identify imbalance case
    // LL
    if(getBalance(curr) > 1 && getBalance(curr->left) > 0){
        // right rotate
        return rightRotate(curr);
    }
    // RR
    else if(getBalance(curr) < -1 && getBalance(curr->right) < 0){
        // left rotate
        return leftRotate(curr);
    }
    // LR
    else if(getBalance(curr) > 1 && getBalance(curr->left) < 0){
        // left rotate subtree, right rotate tree
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // RL
    else if(getBalance(curr) < -1 && getBalance(curr->right) > 0){
        // right rotate subtree, left rotate tree
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

void inOrder(Mahasiswa *curr){
    if(curr == NULL){
        return;
    }
    inOrder(curr->left);
    printf("Age : %d, name: %s\n", curr->age, curr->name);
    inOrder(curr->right);
}

void preOrder(Mahasiswa *curr){
    if(curr == NULL){
        return;
    }
    printf("Age : %d, name: %s\n", curr->age, curr->name);
    preOrder(curr->left);
    preOrder(curr->right);
}

void postOrder(Mahasiswa *curr){
    if(curr == NULL){
        return;
    }
    postOrder(curr->left);
    postOrder(curr->right);
    printf("Age : %d, name: %s\n", curr->age, curr->name);
}

void updateTree(Mahasiswa *root, int age, char newName[100]){
    if(!root){
        printf("Not Found\n");
    }else if(age < root->age){
        updateTree(root->left, age, newName);
    }else if(age > root->age){
        updateTree(root->right, age, newName);
    }else if(age == root->age){
        strcpy(root->name, newName);
        printf("Name updated\n");
    }
}


int main(){

    Mahasiswa *root = NULL;
    root = insertAVL(root, 3, "cindy");
    root = insertAVL(root, 18, "cindy");
    root = insertAVL(root, 21, "cindy");
    root = insertAVL(root, 8, "cindy");
    root = insertAVL(root, 7, "cindy");
    root = insertAVL(root, 6, "cindy");
    root = insertAVL(root, 23, "cindy");

    inOrder(root);
    // preOrder(root);
    // postOrder(root);

    updateTree(root, 21, "jovuta");
    printf("==========================\n");
    inOrder(root);
    return 0;
}