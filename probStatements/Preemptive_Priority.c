#include <stdio.h>

struct Process
{
    int pid, at, bt, priority;
    int remaining_bt;
    int ft, tat, wt;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter AT, BT and Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining_bt = p[i].bt;
    }

    int completed = 0, time = 0;

    while (completed != n)
    {
        int idx = -1;
        int best_priority = 999999;

        // Select process with highest priority (lowest number)
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].remaining_bt > 0)
            {
                if (p[i].priority < best_priority)
                {
                    best_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].remaining_bt--;

            // Process finished
            if (p[idx].remaining_bt == 0)
            {
                p[idx].ft = time + 1;
                completed++;
            }
        }

        time++;
    }

    // Compute TAT and WT
    printf("\nPID\tAT\tBT\tPR\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ft - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ft, p[i].tat, p[i].wt);
    }

    return 0;
}
