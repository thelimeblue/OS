#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void calculateTimes(int n, int at[], int bt[], int ct[], int tat[], int wt[], int priority[], int pid[], int gantt[], int startTimes[], int *ganttSize) {
    int remaining_bt[MAX], currentTime = 0, completed = 0;
    bool isStarted[MAX] = {false};

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    int lastProcess = -1;
    *ganttSize = 0;

    while (completed < n) {
        int idx = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && remaining_bt[i] > 0) {
                if (priority[i] < minPriority || (priority[i] == minPriority && at[i] < at[idx])) {
                    minPriority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (!isStarted[idx]) {
                isStarted[idx] = true;
            }

            // Add to Gantt chart if process changes
            if (lastProcess != idx) {
                gantt[*ganttSize] = pid[idx];
                startTimes[*ganttSize] = currentTime;
                (*ganttSize)++;
                lastProcess = idx;
            }

            remaining_bt[idx]--;
            currentTime++;

            if (remaining_bt[idx] == 0) {
                ct[idx] = currentTime;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    startTimes[*ganttSize] = currentTime; // End time for the last process
}

void printTable(int n, int pid[], int at[], int bt[], int priority[], int ct[], int tat[], int wt[]) {
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }
}

void printGanttChart(int gantt[], int startTimes[], int size) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < size; i++) {
        printf(" P%d |", gantt[i]);
    }
    printf("\n");

    printf("%d", startTimes[0]);
    for (int i = 1; i <= size; i++) {
        printf("   %d", startTimes[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[MAX], at[MAX], bt[MAX], priority[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int gantt[MAX], startTimes[MAX];
    int ganttSize;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", pid[i]);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
    }

    calculateTimes(n, at, bt, ct, tat, wt, priority, pid, gantt, startTimes, &ganttSize);

    printTable(n, pid, at, bt, priority, ct, tat, wt);
    printGanttChart(gantt, startTimes, ganttSize);

    return 0;
}
