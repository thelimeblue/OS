#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int f, int index)
{
    int farthest = -1, pos = -1;

    for (int i = 0; i < f; i++)
    {
        int j;
        for (j = index + 1; j < n; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If a frame's page is not found again in future, replace it
        if (j == n)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

int main()
{
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f];
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    int pageFaults = 0, filled = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check if page is already present
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            // If empty frame available
            if (filled < f)
            {
                frames[filled++] = pages[i];
            }
            else
            {
                int pos = findOptimal(pages, frames, n, f, i);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
