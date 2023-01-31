#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int page_faults = 0, page_hits = 0, frames = 3;
int page_str[3] = {0};

int isPresent(int page)
{
    for (int i = 0; i < frames; i++)
        if (page_str[i] == page)
            return 1;
    return 0;
}

void printFrameStructure()
{
    printf("Current Frame Structure: ");
    for (int k = 0; k < frames; k++)
        printf("%d ", page_str[k]);
    printf("\n");
}

int main()
{
    int incomingPages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int no_of_pages = sizeof(incomingPages) / sizeof(incomingPages[0]);

    // initial filling of frame structure
    for (int i = 0; i < frames; i++)
    {
        page_faults++;
        page_str[i] = incomingPages[i];
    }

    for (int i = frames; i < no_of_pages; i++)
    {
        printFrameStructure();
        if (!isPresent(incomingPages[i]))
        {
            page_faults++;
            for (int j = 1; j < frames; j++)
                page_str[j - 1] = page_str[j];
            page_str[frames - 1] = incomingPages[i];
        }
        else
            page_hits++;
    }

    printf("\nNumber of page hits: %d\n", page_hits);
    printf("Number of page faults: %d\n\n", page_faults);

    return 0;
}