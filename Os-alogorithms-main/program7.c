#include <stdio.h>
 
#define P 5   /* number of processes */
#define R 3   /* number of resource types */
 
int available[R];
int maximum[P][R];
int allocation[P][R];
int need[P][R];
 
void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}
 
int isSafe(int *safeSeq) {
    int work[R];
    int finish[P] = {0};
    for (int j = 0; j < R; j++) work[j] = available[j];
 
    int count = 0;
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j]) break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;   /* no process could proceed: unsafe */
    }
    return 1;
}
 
int requestResources(int pid, int request[]) {
    for (int j = 0; j < R; j++) {
        if (request[j] > need[pid][j]) {
            printf("Error: process has exceeded its maximum claim.\n");
            return 0;
        }
        if (request[j] > available[j]) {
            printf("Request denied: not enough resources available.\n");
            return 0;
        }
    }
    /* tentatively allocate */
    for (int j = 0; j < R; j++) {
        available[j]    -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j]    -= request[j];
    }
 
    int safeSeq[P];
    if (isSafe(safeSeq)) {
        printf("Request can be granted safely.\n");
        return 1;
    } else {
        /* rollback */
        for (int j = 0; j < R; j++) {
            available[j]    += request[j];
            allocation[pid][j] -= request[j];
            need[pid][j]    += request[j];
        }
        printf("Request denied: would lead to an unsafe state.\n");
        return 0;
    }
}
 
int main() {
    printf("Enter available resources of each type (%d types): ", R);
    for (int j = 0; j < R; j++) scanf("%d", &available[j]);
 
    printf("Enter Maximum matrix (%d processes x %d resources):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &maximum[i][j]);
 
    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);
 
    calculateNeed();
 
    int safeSeq[P];
    if (isSafe(safeSeq)) {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is in an UNSAFE state.\n");
    }
 
    int pid;
    int request[R];
    printf("\nEnter process number requesting resources: ");
    scanf("%d", &pid);
    printf("Enter request vector (%d values): ", R);
    for (int j = 0; j < R; j++) scanf("%d", &request[j]);
 
    requestResources(pid, request);
    return 0;
}