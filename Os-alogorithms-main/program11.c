#include <stdio.h>
#include <string.h>
 
#define MAXBLOCKS 30
#define MAXFILES 10
 
int disk[MAXBLOCKS];   /* 0 = free, 1 = allocated */
 
void resetDisk() {
    for (int i = 0; i < MAXBLOCKS; i++) disk[i] = 0;
}
 
void contiguousAllocation() {
    int nf;
    resetDisk();
    printf("\n--- Contiguous Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);
 
    for (int f = 0; f < nf; f++) {
        int start, len;
        printf("File %d - starting block, length: ", f + 1);
        scanf("%d %d", &start, &len);
 
        int ok = 1;
        for (int i = start; i < start + len; i++)
            if (i >= MAXBLOCKS || disk[i] == 1) { ok = 0; break; }
 
        if (!ok) {
            printf("Allocation failed: blocks not free/out of range.\n");
            continue;
        }
        for (int i = start; i < start + len; i++) disk[i] = 1;
        printf("File %d allocated blocks %d to %d\n", f + 1, start, start + len - 1);
    }
}
 
void linkedAllocation() {
    int nf;
    resetDisk();
    printf("\n--- Linked Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);
 
    for (int f = 0; f < nf; f++) {
        int len;
        printf("File %d - number of blocks: ", f + 1);
        scanf("%d", &len);
 
        printf("File %d allocated blocks: ", f + 1);
        int prev = -1, count = 0;
        for (int i = 0; i < MAXBLOCKS && count < len; i++) {
            if (disk[i] == 0) {
                disk[i] = 1;
                printf("%d ", i);
                if (prev != -1) printf("-> ");
                prev = i;
                count++;
            }
        }
        printf("(NULL)\n");
        if (count < len) printf("Warning: disk full, could not allocate all blocks.\n");
    }
}
 
void indexedAllocation() {
    int nf;
    resetDisk();
    printf("\n--- Indexed Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);
 
    for (int f = 0; f < nf; f++) {
        int len;
        printf("File %d - number of data blocks needed: ", f + 1);
        scanf("%d", &len);
 
        int indexBlock = -1;
        for (int i = 0; i < MAXBLOCKS; i++)
            if (disk[i] == 0) { indexBlock = i; disk[i] = 1; break; }
 
        printf("File %d - Index block: %d, Data blocks: ", f + 1, indexBlock);
        int count = 0;
        for (int i = 0; i < MAXBLOCKS && count < len; i++) {
            if (disk[i] == 0) {
                disk[i] = 1;
                printf("%d ", i);
                count++;
            }
        }
        printf("\n");
    }
}
 
int main() {
    int choice;
    printf("Menu:\n1. Contiguous Allocation\n2. Linked Allocation\n");
    printf("3. Indexed Allocation\nEnter choice: ");
    scanf("%d", &choice);
 
    switch (choice) {
        case 1: contiguousAllocation(); break;
        case 2: linkedAllocation(); break;
        case 3: indexedAllocation(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}