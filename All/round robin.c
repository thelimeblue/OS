#include <stdio.h>
#include <stdbool.h>

// Function to display the Gantt Chart
void displayGanttChart(int gantt[], int ganttLen) {
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < ganttLen; i++) {
        printf("----");
    }
    printf("-\n|");

    for (int i = 0; i < ganttLen; i++) {
        if (gantt[i] == -1)
            printf(" I |"); // Idle
        else
            printf("P%d |", gantt[i]);
    }

    printf("\n ");
    for (int i = 0; i < ganttLen; i++) {
        printf("----");
    }
    printf("-\n");

    printf("0");
    for (int i = 1; i <= ganttLen; i++) {
        printf("   %d", i);
    }
    printf("\n");
}

// Round Robin Scheduler Function
void roundRobin(int n, int pid[], int at[], int bt[], int tq) {
    int rt[n], wt[n], tat[n], ct[n];
    for (int i = 0; i < n; i++) rt[i] = bt[i];

    int time = 0, completed = 0;
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    int gantt[1000], ganttLen = 0;

    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                found = true;
                int execTime = (rt[i] > tq) ? tq : rt[i];
                for (int j = 0; j < execTime; j++)
                    gantt[ganttLen++] = pid[i]; // Record each time unit in Gantt chart

                time += execTime;
                rt[i] -= execTime;

                if (rt[i] == 0) {
                    completed++;
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                }
            }
        }

        if (!found) {
            gantt[ganttLen++] = -1; // Idle time
            time++;
        }
    }

    // Display output
    int total_wt = 0, total_tat = 0;
    printf("--------------------------------------------------------------\n");
    printf("| PID | Arrival | Burst | Completion | Turnaround | Waiting |\n");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("| P%-2d |   %2d    |  %2d   |     %2d     |     %2d     |   %2d    |\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("--------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time : %.2f\n", (float)total_tat / n);

    displayGanttChart(gantt, ganttLen);
}

// Main Function
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], tq;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time for Process P%d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process P%d: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    roundRobin(n, pid, at, bt, tq);

    return 0;
}
