#include <stdio.h>

// Function to calculate Completion Time, Turnaround Time, and Waiting Time
void findTimes(int processes[], int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++) {
        if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i]; // CPU was idle
        } else {
            ct[i] = ct[i - 1] + bt[i]; // CPU starts immediately after last process
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

// Function to print Gantt Chart
void printGanttChart(int processes[], int ct[], int at[], int n) {
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n|");

    // Process names
    for (int i = 0; i < n; i++) {
        printf("  P%d   |", processes[i]);
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    // Timeline
    printf("\n");
    int start;
    for (int i = 0; i < n; i++) {
        if (i == 0 || at[i] > ct[i - 1]) {
            start = at[i];
        } else {
            start = ct[i - 1];
        }
        printf("%-8d", start);
    }
    printf("%d\n", ct[n - 1]); // Last completion time
}

// Function to print the full result table and averages
void findavgTime(int processes[], int n, int at[], int bt[]) {
    int ct[n], tat[n], wt[n];
    int total_wt = 0, total_tat = 0;

    findTimes(processes, n, at, bt, ct, tat, wt);

    printf("\n--------------------------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("|   P%d    |      %2d       |     %2d     |       %2d        |       %2d       |      %2d      |\n",
               processes[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("--------------------------------------------------------------------------------\n");
    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;
    printf("Average Waiting Time    = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    printGanttChart(processes, ct, at, n);
}

// Main function with input from user
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], at[n], bt[n];

    // Input process data
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    findavgTime(processes, n, at, bt);
    return 0;
}
