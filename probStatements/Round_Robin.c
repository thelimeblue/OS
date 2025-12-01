#include <stdio.h>

int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int at[n], bt[n], rt[n], ft[n], tat[n], wt[n];
    int i, time = 0, completed = 0;

    printf("Enter Arrival Time & Burst Time of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    while (completed < n)
    {
        int flag = 0;
        for (i = 0; i < n; i++)
        {
            if (rt[i] > 0 && at[i] <= time)
            {
                flag = 1;

                if (rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;
                    ft[i] = time;
                    completed++;
                }
            }
        }
        if (!flag)
            time++; // CPU idle, move time forward
    }

    // Calculate TAT & WT
    for (i = 0; i < n; i++)
    {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Print results
    printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
