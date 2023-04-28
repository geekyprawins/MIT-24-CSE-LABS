__kernel void reverse(__global char *S, __global int *p)
{
	int tid = get_global_id(0);
	int start = p[tid*2];
	int stop = p[tid*2+1];

	char temp;
	for(int i=start,j=stop;i<j;i++,j--)
	{
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
}