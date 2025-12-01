#include <stdio.h>
#include <stdbool.h>

// Global arrays to store actual execution order and time for Gantt Chart
int executionOrder[100];
int executionEndTime[100];

// Swap utility
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Sort processes by Arrival Time, then by Burst Time
void sortByArrivalAndBurst(int n, int at[], int bt[], int pid[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && bt[j] > bt[j + 1])) {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                swap(&pid[j], &pid[j + 1]);
            }
        }
    }
}

// Calculate Completion Time, Turnaround Time, Waiting Time and Execution Order
void calculateTimes(int n, int at[], int bt[], int ct[], int tat[], int wt[], int pid[]) {
    bool completed[n];
    for (int i = 0; i < n; i++) completed[i] = false;

    int completedCount = 0, currentTime = 0, index = 0;

    while (completedCount < n) {
        int shortestJob = -1, minBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && bt[i] < minBurstTime) {
                minBurstTime = bt[i];
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            currentTime++;
        } else {
            currentTime += bt[shortestJob];
            ct[shortestJob] = currentTime;
            tat[shortestJob] = ct[shortestJob] - at[shortestJob];
            wt[shortestJob] = tat[shortestJob] - bt[shortestJob];
            completed[shortestJob] = true;

            executionOrder[index] = shortestJob;
            executionEndTime[index] = currentTime;
            index++;

            completedCount++;
        }
    }
}

// Display Table of Results
void displayResults(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    int total_wt = 0, total_tat = 0;

    printf("-----------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | TAT | WT |\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("|   P%-2d   |      %2d      |     %2d     |       %2d       | %2d  | %2d |\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("-----------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Accurate Gantt Chart based on actual execution order
void printGanttChart(int n, int pid[], int at[], int bt[]) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", pid[executionOrder[i]]);
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("   %d", executionEndTime[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    sortByArrivalAndBurst(n, at, bt, pid);
    calculateTimes(n, at, bt, ct, tat, wt, pid);
    displayResults(n, pid, at, bt, ct, tat, wt);
    printGanttChart(n, pid, at, bt);

    return 0;
}
