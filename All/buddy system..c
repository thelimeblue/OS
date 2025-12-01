#include <stdio.h>
#include <math.h>

#define MAX 1024  // Total memory size (must be power of 2)

struct Block {
    int size;
    int isFree;
};

struct Block memory[MAX];

// Initialize memory with one big free block
void initialize() {
    memory[0].size = MAX;
    memory[0].isFree = 1;
    for (int i = 1; i < MAX; i++) {
        memory[i].size = 0;
        memory[i].isFree = 0;
    }
}

// Find next power of 2 >= n
int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

// Find the buddy block index
int buddyIndex(int index, int blockSize) {
    return index ^ blockSize;
}

// Allocate memory
void allocate(int reqSize) {
    int size = nextPowerOf2(reqSize);  // Find the smallest power of 2 >= requested size
    for (int i = 0; i < MAX; i++) {
        if (memory[i].isFree && memory[i].size >= size) {
            // Split the block until its size is the requested size
            while (memory[i].size > size) {
                int half = memory[i].size / 2;
                memory[i].size = half;
                memory[i + half].size = half;
                memory[i + half].isFree = 1;
            }
            memory[i].isFree = 0;  // Mark the block as used
            printf("Allocated %d bytes at index %d\n", size, i);
            return;
        }
    }
    printf("Allocation failed. Not enough memory.\n");
}

// Free memory
void freeMemory(int index) {
    if (index < 0 || index >= MAX || memory[index].size == 0) {
        printf("Invalid index.\n");
        return;
    }

    memory[index].isFree = 1;  // Mark the block as free
    int blockSize = memory[index].size;
    int buddy = buddyIndex(index, blockSize);

    // Attempt to merge the buddy blocks
    while (buddy < MAX && memory[buddy].isFree && memory[buddy].size == blockSize) {
        // Merge with the buddy block if they are both free and of the same size
        memory[index].size *= 2;  // Double the size of the current block
        memory[buddy].size = 0;  // Mark the buddy block as unused
        memory[buddy].isFree = 0;
        if (buddy < index) index = buddy;  // Update the index if the buddy is smaller
        buddy = buddyIndex(index, memory[index].size);  // Calculate new buddy index
    }
    printf("Freed memory at index %d\n", index);
}

// Show memory status
void showMemory() {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < MAX; i++) {
        if (memory[i].size > 0) {
            printf("Index: %3d | Size: %4d | %s\n", i, memory[i].size, memory[i].isFree ? "Free" : "Used");
        }
    }
    printf("\n");
}

// Main function with user input
int main() {
    initialize();
    int choice, size, index;

    while (1) {
        printf("\n--- Buddy System Menu ---\n");
        printf("1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Show Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                allocate(size);
                break;
            case 2:
                printf("Enter index to free: ");
                scanf("%d", &index);
                freeMemory(index);
                break;
            case 3:
                showMemory();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
