#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct tnode{
    char value;
    struct tnode* left;
    struct tnode* right;
}tnode;

tnode* createNode(char value){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char c){
    return(c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void buildPrefTree(tnode** root, char* prefeq, int *pos){

    if(*root == NULL){
        *root = createNode(prefeq[*pos]);
    }

    if(isOperator(prefeq[*pos])){
        *pos = *pos + 1;
        (*root)->left = createNode(prefeq[*pos]);
        buildPrefTree(&((*root)->left), prefeq, pos);

        *pos = *pos + 1;
        (*root)->right = createNode(prefeq[*pos]);
        buildPrefTree(&((*root)->right), prefeq, pos);
    }
}

tnode* buildPostTree(char postfix[]){
    tnode* stack[100];
    int top = -1;
    int i;

    for(i = 0; postfix[i] != '\0'; i++){
        tnode* newNode = createNode(postfix[i]);

        if(isdigit(postfix[i])){
            stack[++top] = newNode;
        }else if(isOperator(postfix[i])){
            newNode->left = stack[top--];
            newNode->right = stack[top--];
            stack[++top] = newNode;
        }
    }
    return stack[top];
}

int evaluate(tnode* root){
   if(root->value == '+'){
        return evaluate(root->left) + evaluate(root->right);
   }else if(root->value == '-'){
        return evaluate(root->left) - evaluate(root->right);
   }else if(root->value == '/'){
        return evaluate(root->left) / evaluate(root->right);
   }else if(root->value == '*'){
        return evaluate(root->left) * evaluate(root->right);
   }else if(root->value == '^'){
        return (int) pow(evaluate(root->left), evaluate(root->right));
   }else{
        return root->value - '0';
   }
}

void inOrder(tnode* root){
    if(root != NULL){
        if(isOperator(root->value )) putchar('(');
        inOrder(root->left);
        printf("%c ", root->value);
        inOrder(root->right);
        if(isOperator(root->value )) putchar(')');
    }
}

void preOrder(tnode* root){
    if(root != NULL){
        printf("%c ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(tnode* root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->value);
    }
}


int main(){
    char prefeq[] = "+*234";
    char posteq[] = "351^+";
    int pos = 0;
    tnode* root = NULL;

    buildPrefTree(&root, prefeq, &pos);
    printf("In-order Traversal: ");
    inOrder(root);
    printf("\n");
    int res = evaluate(root);
    printf("Hasilnya adalah : %d\n", res);

    tnode* postTree =  buildPostTree(posteq);
    preOrder(postTree);

    // preOrder(root);
    // printf("\n");
    // postOrder(root);
    // printf("\n");
    return 0;
}