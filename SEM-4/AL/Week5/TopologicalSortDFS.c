#include <stdio.h>
#include <stdlib.h>

int a[50][50], visit[50], stack[100],n,t=0;

void dfs(int v)
{
	visit[v]=1;

	for(int i=0;i<n;i++)
	{
		if(a[v][i] && !visit[i])
		{
			dfs(i);
		}
	}

	stack[t++]=v;
}

void printStack()
{
	for(int i=n-1;i>=0;i--)
	{
		printf("%d\n",stack[i]);
	}

	printf("\n");
}

int main()
{
	printf("Enter the Number of Vertices : \n");
	scanf("%d", &n);

	int isEdge;
	for(int i=0; i<n;i++){

		for(int j=0; j<n; j++){

            if(i==j)
                continue;
			printf("Is there an edge between %d and %d ? (0 or 1) ", i,j);
			scanf("%d", &isEdge);

			if(isEdge){
				a[i][j] = 1;
			}
			else{
			a[i][j] = 0;
			}
		}
	}

	for(int i = 0; i<n; i++)
	{
		if(!visit[i])
		{
    		dfs(i);
		}
	}

	printf("The Topological Sort Order is :\n");
	printStack();

	return 0;
}
