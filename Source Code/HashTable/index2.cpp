#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char nama[50];
    char telp[50];
    char email[50];
    struct Entry *next;
} Entry;

typedef struct {
    Entry *table[TABLE_SIZE];
} HashTable;

int hash_function(const char *key) {
    int sum = 0;
    while (*key) {
        sum += *key;
        key++;
    }
    int squared = sum * sum;

    int mid_digits;
    if (squared < 100) {
        mid_digits = squared % 10; 
    } else {
        mid_digits = (squared / 10) % 100;
    }
    return mid_digits % TABLE_SIZE;
}

void init_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

void insert(HashTable *ht, const char *nama, const char *telp, const char *email) {
    int index = hash_function(nama);
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    strcpy(new_entry->nama, nama);
    strcpy(new_entry->telp, telp);
    strcpy(new_entry->email, email);
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;
}

void search(HashTable *ht, const char *nama) {
    int index = hash_function(nama);
    Entry *temp = ht->table[index];
    while (temp) {
        if (strcmp(temp->nama, nama) == 0) {
            printf("Ditemukan: %s - %s - %s\n", temp->nama, temp->telp, temp->email);
            return;
        }
        temp = temp->next;
    }
    printf("Data dengan nama '%s' tidak ditemukan.\n", nama);
}


void deleted(HashTable *ht, const char *nama) {
    int index = hash_function(nama);
    Entry *temp = ht->table[index], *prev = NULL;
    while (temp) {
        if (strcmp(temp->nama, nama) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                ht->table[index] = temp->next;
            }
            free(temp);
            printf("%s berhasil dihapus.\n", nama);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("%s tidak ditemukan.\n", nama);
}

void display(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Entry *temp = ht->table[i];
        if (!temp) {
            printf("NULL\n");
            continue;
        }
        while (temp) {
            printf("[%s, %s, %s] -> ", temp->nama, temp->telp, temp->email);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    HashTable ht;
    init_table(&ht);
    
    insert(&ht, "Rio", "081219883509", "rio@gmail.com");
    insert(&ht, "Reyga", "087875362666", "rey@gmail.com");
    insert(&ht, "Okta", "085952167324", "okta@gmail.com");
    insert(&ht, "Darren", "085952167324", "darren@gmail.com");
    insert(&ht, "Nathan", "085952167324", "nathan@gmail.com");
    insert(&ht, "Martin", "085952167324", "martin@gmail.com");
    
    display(&ht);
    
    // search(&ht, "Reyga");
    // search(&ht, "Budi");  
    
    // deleted(&ht, "Okta");
    // display(&ht);
    
    return 0;
}
