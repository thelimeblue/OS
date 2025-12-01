#include <stdio.h>

int findLRU(int time[], int n)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main()
{
    int pages[30], frame[10], time[10];
    int n, f;
    int pageFaults = 0, counter = 0;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (int i = 0; i < f; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int flag1 = 0, flag2 = 0;

        // Check if page already in frame
        for (int j = 0; j < f; j++)
        {
            if (frame[j] == pages[i])
            {
                counter++;
                time[j] = counter; // Update recent use time
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page not found, insert
        if (flag1 == 0)
        {
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                { // Empty frame
                    counter++;
                    pageFaults++;
                    frame[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty frame → replace LRU
        if (flag2 == 0)
        {
            int pos = findLRU(time, f);
            counter++;
            pageFaults++;
            frame[pos] = pages[i];
            time[pos] = counter;
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
