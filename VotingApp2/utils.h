#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>


int rowCount;
int finalId;

void initDB() {
    FILE *fpr = fopen("./cache.txt", "r");
    FILE *vfpr = fopen("./voters.txt", "r");

    if (fpr == NULL) {
        // create empty file
        printf("Voters DB not found. Creating new one...\n");
        FILE *fpw = fopen("./cache.txt", "w");
        fclose(fpw);
        return;
    }

    rowCount = 0;
    char ch1[200];
    char ch2[200];

    fscanf(fpr, "%d", &rowCount);
    fseek(fpr, ((long)1*rowCount), SEEK_SET);
    fscanf(vfpr, "%d | %[^|] | %[^|\n]", &finalId, ch1, ch2);
    // printf("First read: count=%d, id=%d, name=%s, phone=%s\n", count, id, name, phone);
    
    fclose(fpr);
}