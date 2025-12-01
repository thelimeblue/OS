#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], AT[n], BT[n];
    int FT[n], TAT[n], WT[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process P%d: ", pid[i]);
        scanf("%d %d", &AT[i], &BT[i]);
    }

    // Sort by Arrival Time (FCFS)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (AT[j] > AT[j + 1])
            {
                // Swap AT
                int temp = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp;

                // Swap BT
                temp = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp;

                // Swap PID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // Compute Finish Time
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < AT[i])
            currentTime = AT[i]; // CPU idle until process arrives

        FT[i] = currentTime + BT[i];
        currentTime = FT[i];
    }

    // Compute TAT and WT
    for (int i = 0; i < n; i++)
    {
        TAT[i] = FT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    // Output
    printf("\n----------------------------------------------------------");
    printf("\nPID\tAT\tBT\tFT\tTAT\tWT");
    printf("\n----------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], AT[i], BT[i], FT[i], TAT[i], WT[i]);
    }

    return 0;
}
