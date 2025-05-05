#include <stdio.h>
#include <stdlib.h>

struct nodes {
    int height = 1, value;
    nodes* left;
    nodes* right;

}*root;


int height(nodes* root){
    if(!root) return 0;
    else return root->height;
}

int max_child_height(nodes* node) {
    return height(node->left) > height(node->right) ? height(node->left) : height(node->right);
}

int balance_factor(nodes* node){
    return height(node->left) - height(node->right);
}

nodes* left_rotate(nodes* x){
    nodes* y = x->right;
    nodes* n = y->left;

    y->left = x;
    x->right = n;

    x->height = max_child_height(x) + 1;
    y->height = max_child_height(y) + 1;

    return y;
}

nodes* right_rotate(nodes* x){
    nodes* y = x->left;
    nodes* n = y->right;

    y->right = x;
    x->left = n;

    x->height = max_child_height(x) + 1;
    y->height = max_child_height(y) + 1;

    return y;
}

nodes* balancing(nodes *root, int bf){
    if(bf > 1 && balance_factor(root->left) >= 0){
        puts("Right Rotate Done");
        return right_rotate(root);
    }else if(bf < - 1 && balance_factor(root->right) <= 0){
        puts("Left Rotate Done");
        return left_rotate(root);
    }else if(bf > 1 && balance_factor(root->left)<0){
        puts("Right Rotate & Left Done");
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }else if(bf < -1 && balance_factor(root->right)>0){
        puts("left rotate & Right Rotate Done");
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

nodes* create(int value){
    nodes* new_node = (nodes*)malloc(sizeof(nodes));
    new_node->value = value;
    new_node->height = 1;

    new_node->left = new_node->right = NULL;

    return new_node;
}

nodes* insert(nodes *root, int value){

    if(!root){
        root = create(value);
    }else if(value < root->value){
        root->left = insert(root->left, value);
    }else if(value > root->value){
        root->right = insert(root->right, value);
    }

    root->height = max_child_height(root) + 1;
    int bf = balance_factor(root);
    root = balancing(root, bf);

    return root;
}

nodes* delete_nodes(nodes* root, int value){
    if(!root){
        puts("No tree Builded yet");
        return root;
    }else{
        if(value < root->value){
            root->left = delete_nodes(root->left, value);
        }else if(value > root->value){
            root->right = delete_nodes(root->right, value);
        }else{
            if(!root->left && !root->right){
                free(root);
                root = NULL;
                puts("Gak punya anak");
                return root;
            }else if(root->left){
                nodes* temp = root->left;
                while(temp->right){
                    temp = temp->right;
                }
                root->value = temp->value;
                root->left =  delete_nodes(root->left, temp->value);
            }else if(root->right){
                nodes* temp = root->right;
                while(temp->left){
                    temp = temp->left;
                }
                root->value = temp->value;
                root->right = delete_nodes(root->right, temp->value);
            }
        }
    }

    if(!root) return root;
    root->height = max_child_height(root) + 1;
    int bf = balance_factor(root);
    root = balancing(root, bf);
    return root;
}


void print(nodes* root){
    if(!root) return;
    print(root->left);
    printf("%d -> ", root->value);
    print(root->right);
}

int main(){
    root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 15);
    root = insert(root, 12);
    print(root);
    puts("");

    root = delete_nodes(root, 12);
    print(root);
}