#include <stdio.h>
#include <stdbool.h>

int main() {
    int N, M;

    // User input for number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &N);
    printf("Enter number of resource types: ");
    scanf("%d", &M);

    int Allocation[N][M], Max[N][M], Available[M], Need[N][M];
    bool Finish[N];
    int Work[M];

    // User input for Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &Allocation[i][j]);

    // User input for Max Matrix
    printf("Enter Max Matrix (%d x %d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &Max[i][j]);

    // User input for Available Resources
    printf("Enter Available Resources (%d values):\n", M);
    for (int i = 0; i < M; i++)
        scanf("%d", &Available[i]);

    // Step 1: Calculate Need = Max - Allocation
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    // Step 2: Initialize Work = Available
    for (int i = 0; i < M; i++)
        Work[i] = Available[i];

    // Step 3: Try to find processes that can finish
    bool foundProcess;
    do {
        foundProcess = false;
        for (int i = 0; i < N; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (int j = 0; j < M; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < M; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = true;
                    foundProcess = true;
                    printf("Process P%d has completed.\n", i);
                }
            }
        }
    } while (foundProcess);

    // Step 4: Check if any process is still unfinished
    bool deadlock = false;
    for (int i = 0; i < N; i++) {
        if (!Finish[i]) {
            deadlock = true;
            printf("Process P%d is in deadlock.\n", i);
        }
    }

    if (!deadlock)
        printf("No Deadlock detected. System is in safe state.\n");
    else
        printf("Deadlock detected in the system.\n");

    return 0;
}
