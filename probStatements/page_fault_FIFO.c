#include <stdio.h>

int main()
{
    int frames, pages, page[50], frame[10];
    int i, j, k, flag, pageFaults = 0, front = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter the reference string:\n");
    for (i = 0; i < pages; i++)
    {
        scanf("%d", &page[i]);
    }

    // Initialize frames with -1 (empty)
    for (i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    printf("\nFIFO Page Replacement Process:\n");

    for (i = 0; i < pages; i++)
    {
        flag = 0;

        // Check if page is already in frame (Hit)
        for (j = 0; j < frames; j++)
        {
            if (frame[j] == page[i])
            {
                flag = 1;
                break;
            }
        }

        // If miss → replace using FIFO
        if (flag == 0)
        {
            frame[front] = page[i];
            front = (front + 1) % frames;
            pageFaults++;
        }

        // Print current frames
        printf("After page %d → ", page[i]);
        for (k = 0; k < frames; k++)
        {
            if (frame[k] == -1)
                printf("- ");
            else
                printf("%d ", frame[k]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
