#include <stdio.h>
#include <limits.h>

#define MAX 100

int isPageInFrame(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void printFrames(int frames[], int frameCount) {
    printf("Frames: ");
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

// FIFO Algorithm
void fifo(int pages[], int n, int frameCount) {
    int frames[MAX], front = 0;
    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("\n--- FIFO Algorithm ---\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);
        if (isPageInFrame(frames, frameCount, pages[i])) {
            pageHits++;
            printf("Hit | ");
        } else {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            pageFaults++;
            printf("Fault | ");
        }
        printFrames(frames, frameCount);
    }

    printf("Total Page Hits: %d\nTotal Page Faults: %d\n\n", pageHits, pageFaults);
}

// Optimal Algorithm
void optimal(int pages[], int n, int frameCount) {
    int frames[MAX];
    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("--- Optimal Algorithm ---\n");
    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        int indexToReplace = -1;

        printf("Page %d -> ", currentPage);
        if (isPageInFrame(frames, frameCount, currentPage)) {
            pageHits++;
            printf("Hit | ");
        } else {
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    indexToReplace = j;
                    break;
                }
            }

            if (indexToReplace == -1) {
                int farthest = -1;
                for (int j = 0; j < frameCount; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) break;
                    }
                    if (k == n) { // Never used again
                        indexToReplace = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        indexToReplace = j;
                    }
                }
            }

            frames[indexToReplace] = currentPage;
            pageFaults++;
            printf("Fault | ");
        }
        printFrames(frames, frameCount);
    }

    printf("Total Page Hits: %d\nTotal Page Faults: %d\n\n", pageHits, pageFaults);
}

// LRU Algorithm
void lru(int pages[], int n, int frameCount) {
    int frames[MAX], lastUsed[MAX];
    int pageFaults = 0, pageHits = 0;
    int time = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("--- LRU Algorithm ---\n");
    for (int i = 0; i < n; i++) {
        time++;
        int currentPage = pages[i];
        int indexToReplace = -1;

        printf("Page %d -> ", currentPage);
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == currentPage) {
                pageHits++;
                lastUsed[j] = time;
                found = 1;
                printf("Hit | ");
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    indexToReplace = j;
                    break;
                }
            }

            if (indexToReplace == -1) {
                int lruTime = INT_MAX;
                for (int j = 0; j < frameCount; j++) {
                    if (lastUsed[j] < lruTime) {
                        lruTime = lastUsed[j];
                        indexToReplace = j;
                    }
                }
            }

            frames[indexToReplace] = currentPage;
            lastUsed[indexToReplace] = time;
            pageFaults++;
            printf("Fault | ");
        }
        printFrames(frames, frameCount);
    }

    printf("Total Page Hits: %d\nTotal Page Faults: %d\n\n", pageHits, pageFaults);
}

// Main
int main() {
    int pages[MAX], n, frameCount;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    fifo(pages, n, frameCount);
    optimal(pages, n, frameCount);
    lru(pages, n, frameCount);

    return 0;
}

