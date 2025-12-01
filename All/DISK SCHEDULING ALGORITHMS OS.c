#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Absolute difference
int absDiff(int a, int b) {
    return a > b ? a - b : b - a;
}

// FCFS
int fcfs(int req[], int n, int head) {
    int total = 0;
    printf("FCFS Steps:\n");
    for (int i = 0; i < n; i++) {
        printf("Move from %d to %d, Head movement: %d\n", head, req[i], absDiff(head, req[i]));
        total += absDiff(head, req[i]);
        head = req[i];
    }
    printf("Total Tracks Moved (FCFS): %d\n", total);
    printf("Average Seek Time (FCFS): %.2f\n", (float)total / n);
    return total;
}

// SSTF
int sstf(int req[], int n, int head) {
    int total = 0, done[MAX] = {0}, count = 0;
    printf("SSTF Steps:\n");

    while (count < n) {
        int min = 1e9, index = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && absDiff(head, req[i]) < min) {
                min = absDiff(head, req[i]);
                index = i;
            }
        }
        printf("Move from %d to %d, Head movement: %d\n", head, req[index], min);
        total += min;
        head = req[index];
        done[index] = 1;
        count++;
    }
    printf("Total Tracks Moved (SSTF): %d\n", total);
    printf("Average Seek Time (SSTF): %.2f\n", (float)total / n);
    return total;
}

// SCAN
int scan(int req[], int n, int head, int size) {
    int total = 0, temp[MAX], i, index;
    printf("SCAN Steps:\n");

    for (i = 0; i < n; i++) temp[i] = req[i];
    temp[n++] = head;

    // Sort
    for (i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j] > temp[j + 1]) {
                int t = temp[j]; temp[j] = temp[j + 1]; temp[j + 1] = t;
            }

    for (i = 0; i < n; i++) if (temp[i] == head) { index = i; break; }

    for (i = index; i > 0; i--) {
        printf("Move from %d to %d, Head movement: %d\n", temp[i], temp[i - 1], absDiff(temp[i], temp[i - 1]));
        total += absDiff(temp[i], temp[i - 1]);
    }
    printf("Move from %d to 0, Head movement: %d\n", temp[0], absDiff(temp[0], 0));
    total += absDiff(temp[0], 0);
    for (i = index + 1; i < n; i++) {
        printf("Move from %d to %d, Head movement: %d\n", temp[i], temp[i - 1], absDiff(temp[i], temp[i - 1]));
        total += absDiff(temp[i], temp[i - 1]);
    }

    printf("Total Tracks Moved (SCAN): %d\n", total);
    printf("Average Seek Time (SCAN): %.2f\n", (float)total / n);
    return total;
}

// C-SCAN
int cscan(int req[], int n, int head, int size) {
    int total = 0, temp[MAX], i, index;
    printf("C-SCAN Steps:\n");

    for (i = 0; i < n; i++) temp[i] = req[i];
    temp[n++] = head;

    // Sort
    for (i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j] > temp[j + 1]) {
                int t = temp[j]; temp[j] = temp[j + 1]; temp[j + 1] = t;
            }

    for (i = 0; i < n; i++) if (temp[i] == head) { index = i; break; }

    for (i = index; i < n - 1; i++) {
        printf("Move from %d to %d, Head movement: %d\n", temp[i], temp[i + 1], absDiff(temp[i], temp[i + 1]));
        total += absDiff(temp[i], temp[i + 1]);
    }
    printf("Move from %d to %d, Head movement: %d\n", temp[n - 1], size - 1, absDiff(temp[n - 1], size - 1));
    total += absDiff(temp[n - 1], size - 1);
    printf("Move from %d to 0, Head movement: %d\n", size - 1, absDiff(size - 1, 0));
    total += absDiff(size - 1, 0);
    for (i = 0; i < index; i++) {
        printf("Move from %d to %d, Head movement: %d\n", temp[i], temp[i + 1], absDiff(temp[i], temp[i + 1]));
        total += absDiff(temp[i], temp[i + 1]);
    }

    printf("Total Tracks Moved (C-SCAN): %d\n", total);
    printf("Average Seek Time (C-SCAN): %.2f\n", (float)total / n);
    return total;
}

// Main function
int main() {
    int n, head, size, req[MAX];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    printf("Enter disk requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size: ");
    scanf("%d", &size);

    printf("\nTotal Head Movements:\n");
    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, size);
    cscan(req, n, head, size);

    return 0;
}
