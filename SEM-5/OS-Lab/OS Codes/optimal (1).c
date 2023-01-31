#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FRAMES 4

int incoming_pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
int no_of_pages = sizeof(incoming_pages) / sizeof(incoming_pages[0]);
int page_faults = 0, page_hits = 0;

int available_pages[FRAMES] = {-1};

int isPresent(int page)
{
    for (int i = 0; i < FRAMES; i++)
        if (page == available_pages[i])
            return 1;
    return 0;
}

int predictIndex(int index)
{
    // will store the index of the farthest page which is to be replaced
    int farthest = index;
    int page_to_be_replaced = -1; // will store which page to replace
    for (int i = 0; i < FRAMES; i++)
    {
        int j;
        for (j = index; j < no_of_pages; j++)
        {
            if (available_pages[i] == incoming_pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    page_to_be_replaced = i;
                }
                break;
            }
        }
        // if a page is never referenced in the future, then that is the page to be replaced
        if (j == no_of_pages)
            return i;
    }
    return page_to_be_replaced;
}

void printFrameStructure()
{
    printf("Current Frame Structure: ");
    for (int i = 0; i < FRAMES; i++)
        printf("%d ", available_pages[i]);
    printf("\n");
}

int main()
{
    for (int i = 0; i < FRAMES; i++)
    {
        page_faults++;
        available_pages[i] = incoming_pages[i];
    }

    for (int i = FRAMES; i < no_of_pages; i++)
    {
        if (isPresent(incoming_pages[i]))
        {
            page_hits++;
            continue;
        }
        else
        {
            page_faults++;
            int replace = predictIndex(i + 1);
            available_pages[replace] = incoming_pages[i];
        }
    }

    printf("\nNumber of hits: %d\n", page_hits);
    printf("Number of faults: %d\n\n", page_faults);

    return 0;
}