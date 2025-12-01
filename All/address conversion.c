#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    printf("Select mode:\n1. Paging\n2. Segmentation\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Paging
        int *pageTable, numPages, pageSize, logicalAddress, pageNumber, offset, physicalAddress;

        printf("\n--- Paging Mode ---\n");
        printf("Enter number of pages: ");
        scanf("%d", &numPages);

        pageTable = (int *)malloc(numPages * sizeof(int)); // dynamic memory allocation

        printf("Enter page size: ");
        scanf("%d", &pageSize);

        printf("Enter page table (frame numbers for each page):\n");
        for (int i = 0; i < numPages; i++) {
            printf("Page %d -> Frame: ", i);
            scanf("%d", &pageTable[i]);
        }

        printf("Enter logical address: ");
        scanf("%d", &logicalAddress);

        pageNumber = logicalAddress / pageSize;
        offset = logicalAddress % pageSize;

        if (pageNumber >= numPages) {
            printf("Error: Invalid page number.\n");
        } else {
            physicalAddress = pageTable[pageNumber] * pageSize + offset;
            printf("Physical Address: %d\n", physicalAddress);
        }

        free(pageTable); // free dynamically allocated memory
    }

    else if (choice == 2) {
        // Segmentation
        int base[5], limit[5], segmentNumber, offset, physicalAddress;

        printf("\n--- Segmentation Mode ---\n");
        printf("Enter base and limit for 5 segments:\n");
        for (int i = 0; i < 5; i++) {
            printf("Segment %d - Base: ", i);
            scanf("%d", &base[i]);
            printf("Segment %d - Limit: ", i);
            scanf("%d", &limit[i]);
        }

        printf("Enter segment number and offset: ");
        scanf("%d%d", &segmentNumber, &offset);

        if (segmentNumber < 5 && offset < limit[segmentNumber]) {
            physicalAddress = base[segmentNumber] + offset;
            printf("Physical Address: %d\n", physicalAddress);
        } else {
            printf("Error: Invalid segment number or offset exceeds limit.\n");
        }
    }

    else {
        printf("Invalid choice.\n");
    }

    return 0;
}

