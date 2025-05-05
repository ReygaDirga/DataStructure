#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// inorder
// 1. left
// 2. print
// 3. right

// preorder
// 1. print
// 2. left
// 3. right 

// postOrder
// 1. left
// 2. right
// 3. print


struct Student{
    int id;
    char name[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name){
    struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, char *name){
    // case 1 kalau tree belom dibuat makan kita bikin root nodenya saja
    if(root == NULL){
        return createStudent(id, name);
    }

    // case 2 id yang kita mau insert > current node punya id
    else if(id > root->id){
        root->right = insert(root->right, id, name);
    }

    // case 3 id yang kita mau insert < current node punya id
    else if(id < root->id){
        root->left = insert(root->left, id, name);
    }

    return root;
}

void inorder(struct Student *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf("Student Id : %d, Name : %s\n", root->id, root->name);
    inorder(root->right);
}

void preorder(struct Student *root){
    if(root == NULL){
        return;
    }
    printf("Student Id : %d, Name : %s\n", root->id, root->name);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Student *root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("Student Id : %d, Name : %s\n", root->id, root->name);
}

struct Student *search(struct Student *root, int id){
    // case 1 kalau search gak ketemu
    if(root == NULL){
        puts("NOT FOUND!");
        return NULL;
    }
    // case 2 kalo search ketemu
    else if(root->id == id){
        puts("FOUND");
        return root;
    }
    // case 3 kalau id yang mau di search lebih besar dari current id
    else if(id > root->id){
        return search(root->right, id);
    }
    // case 4 kalau id yang mau di search lebih kecil dari current id
    else if(id < root->id){
        return search(root->left, id);
    }
}

struct Student *update(struct Student *root, int id, char *newName){
    // case 1 kalau update gak ketemu
    if(root == NULL){
        puts("NOT FOUND!");
        return NULL;
    }
    // case 2 kalo update ketemu
    else if(root->id == id){
        puts("FOUND");
        strcpy(root->name, newName);
        return root;
    }
    // case 3 kalau id yang mau di update lebih besar dari current id
    else if(id > root->id){
        return update(root->right, id, newName);
    }
    // case 4 kalau id yang mau di update lebih kecil dari current id
    else if(id < root->id){
        return update(root->left, id, newName);
    }
}

Student *findSuccessor(Student *curr){
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}

Student *deleteStudent(Student *curr, int id){
    if(curr == NULL){
        return NULL;
    }else if(id > curr->id){
        curr->right = deleteStudent(curr->right, id);
    }else if(id < curr->id){
        curr->left = deleteStudent(curr->left, id);
    }else{
        if(curr->left == NULL && curr->right == NULL){
            free(curr);
            return NULL;
        }else if(curr->left == NULL){
            Student *temp = curr->right;
            free(curr);
            return temp;
        }else if(curr->right == NULL){
            Student *temp = curr->left;
            free(curr);
            return temp;
        }else{
            Student *successor = findSuccessor(curr->right);
            curr->id = successor->id;
            strcpy(curr->name, successor->name);
            curr->right = deleteStudent(curr->right, successor->id);
            return curr;
        }
    }

    return curr;
}

Student *deleteAll(Student *root){
    while(root){
        root = deleteStudent(root, root->id);
    }
    return root;
}


int main(){

    struct Student *root = NULL;
    puts("Inserting : ");
    root = insert(root, 100, "Louis");
    root = insert(root, 101, "Brandon");
    root = insert(root, 90, "Angeline");
    root = insert(root, 103, "Bryant");
    root = insert(root, 77, "Calvin");
    root = insert(root, 95, "Giselle");
    root = insert(root, 94, "Nathan");
    root = insert(root, 93, "Marcelle");

    puts("Insert successfully");

    puts("Inorder transerval");
    inorder(root);
    printf("%d\n", root->id);

    puts("Preorder transerval");
    preorder(root);
    printf("%d\n", root->id);
    
    puts("PostOrder transerval");
    postorder(root);
    printf("%d\n", root->id);

    puts("Searching");
    struct Student *searchedStudent = search(root, 378);
    if(searchedStudent != NULL){
        printf("Found Student with id %d and name %s\n", searchedStudent->id, searchedStudent->name);
    }

    puts("Updating");
    struct Student *updatedStudent = update(root, 1, "tommy");
    if(updatedStudent != NULL){
        printf("Update Student with id %d and name %s\n", updatedStudent->id, updatedStudent->name);
    }

    puts("Transversal After Updating");
    inorder(root);

    puts("Deleting");
    root = deleteStudent(root, 100);
    inorder(root);

    puts("Deleting All");
    root = deleteAll(root);
    inorder(root);

    return 0;


}