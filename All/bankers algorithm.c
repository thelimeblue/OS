#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int allocation[P][R], max[P][R], available[R]
    , need[P][R];
    bool finished[P];
    int safeSequence[P], count = 0;

    printf("Enter Allocation Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources (%d values):\n", R);
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < P; i++) {
        finished[i] = false;
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    printf("\n--- Banker's Algorithm Execution ---\n");
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < R; j++)
                        available[j] += allocation[i][j];

                    finished[i] = true;
                    safeSequence[count++] = i;

                    printf("P%d executed. Available: ", i);
                    for (int j = 0; j < R; j++)
                        printf("%d ", available[j]);
                    printf("\n");

                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            printf("System is in Deadlock! No safe sequence.\n");
            return 0;
        }
    }

    printf("\nSystem is in a Safe State.\nSafe Sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 0;
}
