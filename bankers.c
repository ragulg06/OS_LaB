#include <stdio.h>
#include <stdbool.h>

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resource types

    // Allocation matrix
    int alloc[5][3] = {
        {3, 2, 2},
        {2, 1, 3},
        {3, 3, 2},
        {2, 2, 2},
        {3, 1, 1}
    };

    // Maximum matrix
    int max[5][3] = {
        {7, 5, 3},
        {6, 3, 4},
        {9, 6, 5},
        {4, 4, 3},
        {8, 4, 3}
    };

    // Available resources
    int avail[3] = {2, 1, 3};

    int need[5][3], finish[5] = {0}, safeSeq[5], work[3];
    int i, j, k;

    // Calculate need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initialize work = available
    for (j = 0; j < m; j++)
        work[j] = avail[j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) { // All need[i][j] <= work[j]
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state (Deadlock possible).\n");
            return 1;
        }
    }

    printf("The SAFE Sequence is:\n");
    for (i = 0; i < n; i++)
        printf("P%d%s", safeSeq[i], (i < n - 1) ? " -> " : "\n");

    return 0;
}
