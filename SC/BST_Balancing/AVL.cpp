#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    int height;
    struct node *left;
    struct node *right;
}node;

node* CreateNode(int val){
    node* c = (node*)malloc(sizeof(node));
    c->val = val;
    c->height = 1;
    c->left = NULL;
    c->right = NULL;
    return c;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(node* root){
    if(root == NULL ){
        return 0;
    }else{
        return root->height;
    }
}

int getBalance(node* root){
    if(root == NULL){
        return 0;
    }else{
        return height(root->left) - height(root->right);
    }
}

node* LeftRotate(node* x){
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

node* RightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* insert(node* root, int val){
    if(root == NULL){
        return CreateNode(val);
    }else if(val < root->val){
        root->left = insert(root->left, val);
    }else if(val > root->val){
        root->right = insert(root->right, val);
    }else{
        return root;
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if(balance < -1 && val >root->right->val){
        return LeftRotate(root);
    }

    if(balance > 1 && val <root->left->val){
        return RightRotate(root);
    }

    if(balance < -1 && val < root->right->val){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    if(balance > 1 && val > root->left->val){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    return root;
}

node* deletee(node* root, int val){
    if(root == NULL){
        return root;
    }else if(val < root->val){
        root->left = deletee(root->left, val);
    }else if(val > root->val){
        root->right = deletee(root->right, val);
    }else {  
        // Kasus 1 & 2: Node tanpa anak atau 1 anak
        if(root->left == NULL || root->right == NULL){  
            node* temp;
            if (root->left != NULL) {
                temp = root->left;
            } else {
                temp = root->right;
            }
            free(root);  
            return temp;  
        }

        //        50
        //        / \
        //       30  70
        //      / \  / \
        //     20 40 60

        // Kasus 3: Node dengan 2 anak → cari inorder successor
        node* temp = root->right;
        // node* temp = 70 dan kebawahnya
        while(temp->left != NULL) temp = temp->left; // lakukan looping ke anak kiri terdalam
        root->val = temp->val;
        // 50 = 60

        //        60
        //        / \
        //       30  70
        //      / \  / \
        //     20 40 60

        root->right = deletee(root->right, temp->val);
        // root->right = deletee(root->right, 60);
    }
    if(root == NULL){
        return root;
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if(balance < -1 && getBalance(root->right) <= 0){
        return LeftRotate(root);
    }

    if(balance > 1 && getBalance(root->left) >= 0){
        return RightRotate(root);
    }

    if(balance < -1 && getBalance(root->right) > 0){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    if(balance > 1 && getBalance(root->left) < 0){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    return root;
}

void inOrder(node* root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->val);
        inOrder(root->right);
    }
}

int main(){

    node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    
    inOrder(root);
    printf("\n");
    root = deletee(root, 30); 
    inOrder(root);


    return 0;
}