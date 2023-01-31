#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FRAMES 3

int incoming_pages[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};
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

int predictIndex(int current_index)
{
    int farthest = current_index;
    int page_to_be_replaced = -1;
    for (int i = 0; i < FRAMES; i++)
    {
        int j;
        for (j = current_index; j >= 0; j--)
        {
            if (available_pages[i] == incoming_pages[j])
            {
                if (j < farthest)
                {
                    farthest = j;
                    page_to_be_replaced = i;
                }
                break;
            }
        }
        if (j == -1) // page not found
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
            int replace = predictIndex(i - 1);
            available_pages[replace] = incoming_pages[i];
        }
    }

    printf("\nNumber of hits: %d\n", page_hits);
    printf("Number of faults: %d\n\n", page_faults);

    return 0;
}