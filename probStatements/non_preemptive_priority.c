#include <stdio.h>

struct Process
{
    int pid;
    int bt; // Burst Time
    int priority;
    int ft;  // Finish Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        printf("Enter Priority for P%d (lower = higher priority): ", i + 1);
        scanf("%d", &p[i].priority);

        p[i].pid = i + 1;
    }

    // Sorting based on Priority (Non-preemptive)
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].priority < p[i].priority)
            { // higher priority first
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int current_time = 0;

    // Calculate FT, TAT, WT
    for (int i = 0; i < n; i++)
    {
        current_time += p[i].bt;
        p[i].ft = current_time;

        p[i].tat = p[i].ft; // since AT = 0
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Output table
    printf("\n-----------------------------------------------------------\n");
    printf("PID\tBT\tPriority\tFT\tTAT\tWT\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].priority, p[i].ft, p[i].tat, p[i].wt);
    }

    return 0;
}
