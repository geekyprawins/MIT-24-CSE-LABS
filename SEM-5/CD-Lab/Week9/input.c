#include <stdio.h>
#include <conio.h>
main()
{
    int ar[100], i, n, j, counter;
    // printf("Enter the size of the array ");
    // scanf("%d", &n);
    // printf("\n Now enter the elements of the array");
    for (i = 0; i < n; i = i + 1)
    {
        // scanf("%d", &ar[i]); /* input array*/
    }
    // printf("\n All the prime numbers in the array are -");
    for (i = 0; i < n; i = i + 1)
    {
        counter = 0;
        for (j = 2; j < ar; j = j + 1)
        {
            if (ar % j == 0)
            {
                counter = 1; // remove this line for testcase2
            }
        }
        if (counter == 0)
        {
            // printf("\t %d", ar[i]);
        }
        else
        {
            // printf("\n");
        }
    }
}
