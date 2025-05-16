#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodes {
    char name[101];
    int price;
    char cate[20];
    char avail[20];
    int height;
    struct nodes* left;
    struct nodes* right;
} *node = NULL;

typedef struct nodes nodes;

nodes* createNode(char* name, int price, char* cate, char* avail){
    nodes* newNode = (nodes*)malloc(sizeof(nodes));
    strcpy(newNode->name, name);
    newNode->price = price;
    strcpy(newNode->cate, cate);
    strcpy(newNode->avail, avail);
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void enterCont(){
    printf("Press enter to continue...");
    getchar();
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(nodes* N){
    return N ? N->height : 0;
}

int getBalance(nodes* N){
    return N ? height(N->left) - height(N->right) : 0;
}

nodes* rightRotate(nodes* y){
    nodes* x = y->left;
    nodes* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

nodes* leftRotate(nodes* x){
    nodes* y = x->right;
    nodes* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int validationName(char* name){
    if(strncmp(name, "sally", 5)!=0 || strlen(name) < 5 || strlen(name) > 20){
        return -1;
    }
    
    int space = 0, letterAfterSpace = 0, flag = 0, x = strlen(name);
    for(int i = 0; i < x; i++){
        if(name[i] == ' ' && flag == 0){
            space++;
            flag = 1;
        }
        if(name[i] == ' ' && flag == 1){
            letterAfterSpace++;
            flag = 0;
        }
    }

    if(space >  0 && letterAfterSpace > 0){
        return 1;
    }
    return -1;
}

nodes* insertAVL(nodes* root, nodes* newNode){
    if(root == NULL) return newNode;

    if(strcmp(newNode->name, root->name) < 0){
        root->left = insertAVL(root->left, newNode);
    }else if(strcmp(newNode->name, root->name) > 0){
        root->right = insertAVL(root->right, newNode);
    }else{
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if(balance > 1 && strcmp(newNode->name, root->left->name) < 0){
        return rightRotate(root);
    }
    if(balance < -1 && strcmp(newNode->name, root->right->name) > 0){
        return leftRotate(root);
    }
    if(balance > 1 && strcmp(newNode->name, root->left->name) > 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && strcmp(newNode->name, root->right->name) < 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

nodes* insert(nodes* root){
    system("cls || clear");
    char name[101], cate[20], avail[20];
    int price;

    do{
        printf("Insert name: ");
        scanf("%[^\n]", name); getchar();
    }while(validationName(name) == -1);

    do{
        printf("Insert price: ");
        scanf("%d", &price); getchar();
    }while(price <= 50000 || price >= 1000000);

    do{
        printf("Insert category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", cate); getchar();
    }while(strcmp(cate, "Hair Care") != 0 && strcmp(cate, "Nail Care") != 0 && strcmp(cate, "Body Care") != 0);

    do{
        printf("Insert availability [Available | Not Available]: ");
        scanf("%[^\n]", avail); getchar();
    }while(strcmp(avail, "Available") != 0 && strcmp(avail, "Not Available") != 0);

    nodes* newNode = createNode(name, price, cate, avail);
    root = insertAVL(root, newNode);

    printf("Insert success\n");
    enterCont();

    return root;
}

void view(nodes* root){
    if(root == NULL) return;
    view(root->left);
    printf("Name: %s | Price: %d | Category: %s | Availability: %s\n", root->name, root->price, root->cate, root->avail);
    view(root->right);
}

nodes* minValueNode(nodes* root){
    nodes* curr = root;
    while(curr && curr->left != NULL)
        curr = curr->left;
    return curr;
}

nodes* deleteNode(nodes* root, char* key){
    if(root == NULL) return root;

    if(strcmp(key, root->name) < 0){
        root->left = deleteNode(root->left, key);
    } else if(strcmp(key, root->name) > 0){
        root->right = deleteNode(root->right, key);
    } else {
        if((root->left == NULL) || (root->right == NULL)){
            nodes* temp = root->left ? root->left : root->right;

            if(temp == NULL){
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            nodes* temp = minValueNode(root->right);
            strcpy(root->name, temp->name);
            root->price = temp->price;
            strcpy(root->cate, temp->cate);
            strcpy(root->avail, temp->avail);
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if(root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if(balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if(balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

nodes* deleted(nodes* root){
    system("cls || clear");
    char delName[101];
    printf("Masukin nama yang mau dihapus: ");
    scanf("%[^\n]", delName); getchar();

    root = deleteNode(root, delName);
    printf("Delete sukses\n");
    enterCont();
    return root;
}


int main(){
    int choice = -1;

    do{
        do{
            printf("Menu:\n");
            printf("1. View\n");
            printf("2. Insert\n");
            printf("3. Delete\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice); getchar();
        }while(choice < 1 || choice > 4);

        switch(choice){
            case 1:
                view(node);
                break;
            case 2:
                node = insert(node);
                break;
            case 3:
                node = deleted(node);
                break;
            case 4:
                printf("Exit...\n");
                return 0;
        }
    }while(1);
}
