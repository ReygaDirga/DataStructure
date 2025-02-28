#include <stdio.h>
#include <stdlib.h>

typedef struct tnode{
    int value;
    struct tnode *left;
    struct tnode *right;
}tnode;

tnode* createNode(int value){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    c->value = value;
    c->left = NULL;
    c->right = NULL;
    return c;
}

tnode* buildBST(tnode* root, int value){
    if(root == NULL){
        printf("Value: %d ", value);
        printf("\n");
        return createNode(value);
    }
    if(value < root->value){
        root->left = buildBST(root->left, value);
    }else{
        root->right = buildBST(root->right, value);
    }
    return root;
}

int search(tnode* root, int value){
    if(root == NULL){
        return -1;
    }
    if(root->value == value){
        return root->value;
    }else if(value < root->value){
        return search(root->left, value);
    }else if(value > root->value){
        return search(root->right, value);  
    }

    return root->value;
}

void inOrder(tnode* root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
}

void preOrder(tnode* root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->value);
    inOrder(root->left);
    inOrder(root->right);
}

void postOrder(tnode* root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    inOrder(root->right);
    printf("%d ", root->value);
}

tnode* delNode(tnode* root, int value){
    if(root == NULL){
        return root;
    }
    if(value < root->value){
        root->left = delNode(root->left, value);
    }else if(value > root->value){
        root->right = delNode(root->right, value);
    }else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }else if(root->right == NULL){
            tnode* temp = root->left;
            free(root);
            return temp;
        }else if(root->left == NULL){
            tnode* temp = root->right;
            free(root);
            return temp;
        }else{
            tnode* temp = root->right;
            while(temp->left != NULL){
                temp = temp->left;
            }
            root->value = temp->value;
            delNode(root->right, temp->value);
        }
    }
}

int main(){
    tnode* root = NULL;
    root = buildBST(root, 20);
    root = buildBST(root, 15);
    root = buildBST(root, 19);
    root = buildBST(root, 16);
    root = buildBST(root, 18);
    root = buildBST(root, 17);

    // printf("%d\n", root->value);

    // printf("%d\n", search(root, 11));

    inOrder(root);
    printf("\n");
    root = delNode(root, 19);
    inOrder(root);
    return 0;
}