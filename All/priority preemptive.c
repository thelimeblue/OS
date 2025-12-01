#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int main() {
    int n;
    int pid[MAX], at[MAX], bt[MAX], priority[MAX];
    int rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    bool completed[MAX] = {false};

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time for Process P%d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process P%d: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process P%d (lower number = higher priority): ", pid[i]);
        scanf("%d", &priority[i]);
    }

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    int completedCount = 0, time = 0;
    int gantt[MAX], ganttTime[MAX], gIndex = 0;

    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && priority[i] < highestPriority) {
                highestPriority = priority[i];
                idx = i;
            }
        }

        if (idx != -1) {
            rt[idx]--;

            // Record in Gantt chart
            gantt[gIndex] = pid[idx];
            ganttTime[gIndex] = time;
            gIndex++;

            if (rt[idx] == 0) {
                completed[idx] = true;
                completedCount++;
                ct[idx] = time + 1;
            }
        } else {
            // Idle time
            gantt[gIndex] = -1;
            ganttTime[gIndex] = time;
            gIndex++;
        }

        time++;
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("----------------------------------------------------------------------------\n");
    printf("| PID | Arrival | Burst | Priority | Completion | Turnaround | Waiting    |\n");
    printf("----------------------------------------------------------------------------\n");

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("| P%-2d |   %2d    |   %2d  |    %2d    |     %2d     |     %2d     |    %2d     |\n",
               pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    printf("----------------------------------------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gIndex; i++) {
        if (gantt[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", gantt[i]);
    }
    printf("\n");

    for (int i = 0; i < gIndex; i++) {
        printf("%-5d", ganttTime[i]);
    }
    printf("%-5d\n", time);  // Final time

    return 0;
}
