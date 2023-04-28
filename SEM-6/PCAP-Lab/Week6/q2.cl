__kernel void selection(__global int *A,__global *B)
{
	int pos=0;
	int tid=get_global_id(0);
	int data=A[tid];
	int n=get_global_size(0);

	for(int i=0;i<n;i++)
	{
		if((A[i]<data)||(A[i]==data && i<tid))
			pos++;
	}
	B[pos]=data;
}