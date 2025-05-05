#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tnode {
    char value;
    struct tnode* left;
    struct tnode* right;
} tnode;

int operatorr(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

tnode* prepo(char* exp) {
    tnode* nodeStack[100];
    char opStack[100];
    int nodeTop = -1, opTop = -1;
    
    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];
        
        if (isalnum(c)) {
            tnode* newNode = (tnode*)malloc(sizeof(tnode));
            newNode->value = c;
            newNode->left = newNode->right = NULL;
            nodeStack[++nodeTop] = newNode;
        } else {
            while (opTop != -1 && operatorr(opStack[opTop]) >= operatorr(c)) {
                tnode* newNode = (tnode*)malloc(sizeof(tnode));
                newNode->value = opStack[opTop--];
                newNode->right = nodeStack[nodeTop--];
                newNode->left = nodeStack[nodeTop--];
                nodeStack[++nodeTop] = newNode;
            }
            opStack[++opTop] = c;
        }
    }
    
    while (opTop != -1) {
        tnode* newNode = (tnode*)malloc(sizeof(tnode));
        newNode->value = opStack[opTop--];
        newNode->right = nodeStack[nodeTop--];
        newNode->left = nodeStack[nodeTop--];
        nodeStack[++nodeTop] = newNode;
    }
    
    return nodeStack[0];
}

void prefix(tnode* root) {
    if (root != NULL) {
        printf("%c ", root->value);
        prefix(root->left);
        prefix(root->right);
    }
}

void postfix(tnode* root) {
    if (root != NULL) {
        postfix(root->left);
        postfix(root->right);
        printf("%c ", root->value); 
    }
}

int main() {
    char ekspresi[] = "3+5*2-8";
    tnode* root = prepo(ekspresi);
    
    printf("Prefix: ");
    prefix(root);
    printf("\n");
    
    printf("Postfix: ");
    postfix(root);
    printf("\n");
    
    return 0;
}
