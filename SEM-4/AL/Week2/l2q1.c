#include <stdio.h>

int bubble_sort(int num[], int n){
	int opcount = 0,temp;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n-1-i;j++)
		{
			if(num[j+1] < num[j])
			{
				temp = num[j+1];
				num[j+1] = num[j];
				num[j] = temp;
			}
			
			opcount++;
		}
	}
	printf("Sorted array is :\n");

	for(int i = 0;i<n;i++)
	{
			printf("%d ",num[i]);
	}
	printf("\n");

	return opcount;
}


int main()
{


	int n;
	printf("Enter the size of array: \n");
	scanf("%d",&n);
	int temp,opcount_worst, opcount_best;
	int num1[n];
	int num2[n];
	
	for(int i = n-1;i>=0;i--)
	{
		num1[n-i-1] = i;
	}
	printf("Worst case array is :\n");

	for(int i = 0;i<n;i++)
	{
			printf("%d ",num1[i]);
	}
	printf("\n");
	
    opcount_worst = bubble_sort(num1,n);
    printf("Worst case Opcount ---> %d \n",opcount_worst);

    for(int i=0; i<n;i++){
    	num2[i] = i;
    }
	printf("Best case array is :\n");

	for(int i = 0;i<n;i++)
	{
			printf("%d ",num2[i]);
	}
	printf("\n");


    opcount_best = bubble_sort(num2,n);
	printf("Best case Opcount ---> %d \n",opcount_best);
}