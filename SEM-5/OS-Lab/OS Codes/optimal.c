#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define frame 3

void displayarr(int arr[])
{
    for (int i = 0; i < frame; i++)
    {
        printf("%d  ", arr[i]);
    }
}

int returnMax(int arr[], int length)
{
    // Initialize max with first element of array.
    int max = arr[0];
    // Loop through the array
    for (int i = 0; i < length; i++)
    {
        // Compare elements of array with max
        if (arr[i] > max)
            max = arr[i];
    }
    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int optimal(int arr[], int n)
{
    int frames[frame], faults = 0;
    for (int i = 0; i < frame; i++)
    {
        frames[i] = -1;
    }
    // Initially populate the frame array fully:
    for (int i = 0; i < frame; i++)
    {
        printf("\n");
        frames[i] = arr[i];
        displayarr(frames);
        printf("M");
    }

    printf("\n");
    for (int i = frame; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < frame; j++)
        {
            if (frames[j] == arr[i])
            {
                displayarr(frames);
                printf("H\n");
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            continue;
        }
        // Not available in frames.
        if (flag == 0)
        {
            // Start iterating from behind.
            int lastIndex[n - i];
            for (int j = 0; j < n - i; j++)
            {
                lastIndex[j] = -1;
            }
            for (int j = n - 1; j >= i + 1; j--)
            {
                lastIndex[arr[j]] = j;
            }
            bool ifNegative = false;
            // Iterate through frames to see which can be replaced.
            for (int j = 0; j < frame; j++)
            {
                if (lastIndex[frames[j]] == -1)
                {
                    // Replace this page.
                    frames[j] = arr[i];
                    displayarr(frames);
                    printf("M\n");
                    faults++;
                    ifNegative = true;
                    break;
                }
            }
            if (!ifNegative)
            {
                // Select element with last occuring index.
                int maxIndex = returnMax(lastIndex, n);
                int reqIndex = -1;
                for (int k = 0; k < n; k++)
                {
                    if (lastIndex[k] == maxIndex)
                    {
                        reqIndex = k;
                    }
                }
                frames[reqIndex] = arr[i];
                faults++;
                displayarr(frames);
                printf("M\n");
            }
        }
    }

    return faults + frame;
}

int main()
{
    printf("Enter size of input string\n");
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Enter input string\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int faults = optimal(arr, n);
    printf("No. of faults is %d", faults);
    return 0;
}