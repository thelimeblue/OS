#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], ft[n], tat[n], wt[n], p[n];

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sorting processes by burst time (SJF)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (bt[j] > bt[j + 1])
            {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculating Finish Time, TAT, WT
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        current_time += bt[i];
        ft[i] = current_time;
        tat[i] = ft[i]; // Since Arrival Time = 0
        wt[i] = tat[i] - bt[i];
    }

    // Output
    printf("\nP\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], ft[i], tat[i], wt[i]);
    }

    return 0;
}
