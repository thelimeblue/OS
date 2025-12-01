#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

// Tracks the Gantt chart timeline
void calculateTimes(int n, int at[], int bt[], int ct[], int tat[], int wt[], int timeline[], int *timelineLength) {
    bool completed[n];
    int remainingBt[n];
    for (int i = 0; i < n; i++) {
        completed[i] = false;
        remainingBt[i] = bt[i];
    }

    int completedCount = 0, currentTime = 0;
    *timelineLength = 0;

    while (completedCount < n) {
        int shortestJob = -1, minBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && remainingBt[i] < minBurstTime && remainingBt[i] > 0) {
                minBurstTime = remainingBt[i];
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            timeline[(*timelineLength)++] = -1; // idle time
            currentTime++;
        } else {
            timeline[(*timelineLength)++] = shortestJob; // store index
            remainingBt[shortestJob]--;
            currentTime++;

            if (remainingBt[shortestJob] == 0) {
                completed[shortestJob] = true;
                ct[shortestJob] = currentTime;
                tat[shortestJob] = ct[shortestJob] - at[shortestJob];
                wt[shortestJob] = tat[shortestJob] - bt[shortestJob];
                completedCount++;
            }
        }
    }
}

void displayResults(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    int total_wt = 0, total_tat = 0;

    printf("-----------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | TAT  | WT  |\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("|   P%-2d   |      %2d      |     %2d     |       %2d       |  %2d  | %2d  |\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("-----------------------------------------------------------------\n");

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void displayGanttChart(int timeline[], int timelineLength, int pid[]) {
    printf("\nGantt Chart:\n");
    printf(" ");

    // Top border
    for (int i = 0; i < timelineLength; i++) printf("----");
    printf("-\n|");

    // Process names
    for (int i = 0; i < timelineLength; i++) {
        if (timeline[i] == -1)
            printf(" I |");
        else
            printf("P%d |", pid[timeline[i]]);
    }

    // Bottom border
    printf("\n ");
    for (int i = 0; i < timelineLength; i++) printf("----");
    printf("-\n");

    // Time labels
    printf("0");
    for (int i = 1; i <= timelineLength; i++) printf("   %d", i);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], timeline[1000], timelineLength;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time of P%d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    sortByArrivalAndBurst(n, at, bt, pid);
    calculateTimes(n, at, bt, ct, tat, wt, timeline, &timelineLength);
    displayResults(n, pid, at, bt, ct, tat, wt);
    displayGanttChart(timeline, timelineLength, pid);

    return 0;
}
