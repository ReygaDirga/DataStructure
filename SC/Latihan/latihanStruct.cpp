#include <stdio.h>
#include <string.h>

struct game {
    char name[50];
    char rank[100];
    int hp;
    int magic;
    int gold;
};

int count = 0;

int main() {
    struct game data[100];
    int choice = -1;

    do {
        puts("1. Create");
        puts("2. View");
        puts("3. Delete");
        puts("4. Upgrade");
        puts("5. Exit");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
        case 1:
            printf("Masukkan nama: ");
            scanf("%[^\n]", data[count].name);
            getchar();

            do {
                printf("Masukkan rank (silver/bronze/gold): ");
                scanf("%s", data[count].rank);
                getchar();
            } while (strcmp(data[count].rank, "silver") != 0 &&
                     strcmp(data[count].rank, "bronze") != 0 &&
                     strcmp(data[count].rank, "gold") != 0);

            printf("Masukkan Hp: ");
            scanf("%d", &data[count].hp);
            printf("Masukkan Magic Point: ");
            scanf("%d", &data[count].magic);
            printf("Masukkan gold: ");
            scanf("%d", &data[count].gold);
            count++;
            break;

        case 2:
            if (count == 0) {
                printf("Data kosong!\n");
            } else {
                for (int i = 0; i < count; i++) {
                    printf("\nNo: %d\n", i + 1);
                    printf("Nama: %s\n", data[i].name);
                    printf("Rank: %s\n", data[i].rank);
                }
            }
            break;

        case 3: {
            if (count == 0) {
                printf("Tidak ada data untuk dihapus!\n");
                break;
            }
            char pilih[50];
            printf("Nama yang mau dihapus: ");
            scanf("%[^\n]", pilih);
            getchar(); 

            int found = -1;
            for (int i = 0; i < count; i++) {
                if (strcmp(pilih, data[i].name) == 0) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                for (int i = found; i < count - 1; i++) {
                    data[i] = data[i + 1];
                }
                count--;
                printf("Data berhasil dihapus!\n");
            } else {
                printf("Data tidak ditemukan!\n");
            }
            break;
        }

        case 4: {
            if (count == 0) {
                printf("Tidak ada data untuk di-upgrade!\n");
                break;
            }
            char pilih[50];
            printf("Nama yang mau di-upgrade: ");
            scanf("%[^\n]", pilih);
            getchar();

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(pilih, data[i].name) == 0) {
                    data[i].hp += 150;
                    data[i].magic += 150;
                    data[i].gold -= 50;
                    printf("Data berhasil di-upgrade!\n");
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Data tidak ditemukan!\n");
            }
            break;
        }
        case 5:
            return 0;
        }
    } while (choice != 5);

    return 0;
}
