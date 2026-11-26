#include <stdio.h>
 
#define MAX 20
 
void firstFit(int bsize[], int bn, int psize[], int pn) {
    int allocation[MAX];
    int block[MAX];
    for (int i = 0; i < bn; i++) block[i] = bsize[i];
    for (int i = 0; i < pn; i++) allocation[i] = -1;
 
    for (int i = 0; i < pn; i++) {
        for (int j = 0; j < bn; j++) {
            if (block[j] >= psize[i]) {
                allocation[i] = j;
                block[j] -= psize[i];
                break;
            }
        }
    }
    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < pn; i++) {
        printf("P%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1) printf("B%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}
 
void bestFit(int bsize[], int bn, int psize[], int pn) {
    int allocation[MAX];
    int block[MAX];
    for (int i = 0; i < bn; i++) block[i] = bsize[i];
    for (int i = 0; i < pn; i++) allocation[i] = -1;
 
    for (int i = 0; i < pn; i++) {
        int bestIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (block[j] >= psize[i]) {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            block[bestIdx] -= psize[i];
        }
    }
    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < pn; i++) {
        printf("P%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1) printf("B%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}
 
void worstFit(int bsize[], int bn, int psize[], int pn) {
    int allocation[MAX];
    int block[MAX];
    for (int i = 0; i < bn; i++) block[i] = bsize[i];
    for (int i = 0; i < pn; i++) allocation[i] = -1;
 
    for (int i = 0; i < pn; i++) {
        int worstIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (block[j] >= psize[i]) {
                if (worstIdx == -1 || block[j] > block[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            block[worstIdx] -= psize[i];
        }
    }
    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < pn; i++) {
        printf("P%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1) printf("B%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}
 
int main() {
    int bn, pn;
    int bsize[MAX], psize[MAX];
 
    printf("Enter number of memory blocks: ");
    scanf("%d", &bn);
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < bn; i++) scanf("%d", &bsize[i]);
 
    printf("Enter number of processes: ");
    scanf("%d", &pn);
    printf("Enter sizes of processes: ");
    for (int i = 0; i < pn; i++) scanf("%d", &psize[i]);
 
    firstFit(bsize, bn, psize, pn);
    bestFit(bsize, bn, psize, pn);
    worstFit(bsize, bn, psize, pn);
    return 0;
}