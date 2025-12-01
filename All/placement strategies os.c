#include <stdio.h>

#define MAX 100

// Function to reset allocation array
void resetAlloc(int allocation[], int n) {
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
}

// External Fragmentation Calculation
void calculateExternalFragmentation(int blockSize[], int blocks, int allocation[], int processes) {
    int externalFragmentation = 0;
    int unallocated = 0;

    // Check if there is any unallocated process
    for (int i = 0; i < processes; i++) {
        if (allocation[i] == -1) {
            unallocated = 1;
            break;
        }
    }

    // If there is any unallocated process, sum up all the remaining block sizes
    if (unallocated) {
        for (int i = 0; i < blocks; i++) {
            externalFragmentation += blockSize[i];
        }
        printf("Total External Fragmentation: %d\n", externalFragmentation);
    } else {
        printf("No External Fragmentation (all processes allocated).\n");
    }
}

// First Fit Strategy
void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    resetAlloc(allocation, processes);

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d -> ", i + 1);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    calculateExternalFragmentation(blockSize, blocks, allocation, processes);
}

// Next Fit Strategy
void nextFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    resetAlloc(allocation, processes);
    int lastPos = 0;

    for (int i = 0; i < processes; i++) {
        int j = lastPos;
        int count = 0;

        while (count < blocks) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastPos = j;
                break;
            }
            j = (j + 1) % blocks;
            count++;
        }
    }

    printf("\nNext Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d -> ", i + 1);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    calculateExternalFragmentation(blockSize, blocks, allocation, processes);
}

// Best Fit Strategy
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    resetAlloc(allocation, processes);

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d -> ", i + 1);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    calculateExternalFragmentation(blockSize, blocks, allocation, processes);
}

// Worst Fit Strategy
void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    resetAlloc(allocation, processes);

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d -> ", i + 1);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    calculateExternalFragmentation(blockSize, blocks, allocation, processes);
}

int main() {
    int blocks, processes;
    int blockSize[MAX], processSize[MAX];
    int originalBlockSize[MAX];

    printf("Enter number of free memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter size of each block:\n");
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i]; // Save original for reuse
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    // Call all strategies
    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i];
    firstFit(blockSize, blocks, processSize, processes);

    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i];
    nextFit(blockSize, blocks, processSize, processes);

    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i];
    bestFit(blockSize, blocks, processSize, processes);

    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i];
    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}
