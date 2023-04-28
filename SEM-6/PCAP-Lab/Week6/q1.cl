__kernel void strCpy(__global char *s,__global char *res,int len)
{
	int tid= get_global_id(0);

	for(int i=0;i<len;i++)
		res[len*tid+i]=s[i];
}