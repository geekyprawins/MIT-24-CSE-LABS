#include<stdio.h>
#include<stdlib.h>

int opcount = 0;

int partition(int arr[], int size, int index, int sum)
{
    opcount++;
    if(sum == 0)
    {

        return 1;
    }
    if(size - index == 1)
    {
        if(arr[index] == sum) return 1;
        else return 0;
    }
    return partition(arr, size, index+1, sum) | partition(arr, size, index+1, sum-arr[index]);
}

int main()
{
    int size = 0;
    printf("Enter size of array : ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter array elements : ");
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    if(sum%2)
    {
        printf("Total sum is odd. Partition not possible.\n");
        exit(0);
    }

    if(partition(arr, size, 0, sum/2)) printf("Partition possible.\n");
    else printf("Partition not possible.\n");
    printf("Opcount : %d\n", opcount);
    return 0;
}