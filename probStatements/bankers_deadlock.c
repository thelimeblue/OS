#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], avail[10];
    int need[10][10];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate NEED matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finished[10] = {0};
    int safeSeq[10];
    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int p = 0; p < n; p++)
        {
            if (!finished[p])
            {
                bool flag = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[p][j] > avail[j])
                    {
                        flag = false;
                        break;
                    }
                }

                if (flag)
                {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[p][j];

                    safeSeq[count++] = p;
                    finished[p] = 1;
                    found = true;
                }
            }
        }

        if (!found)
        {
            printf("\nSystem is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");
    return 0;
}
