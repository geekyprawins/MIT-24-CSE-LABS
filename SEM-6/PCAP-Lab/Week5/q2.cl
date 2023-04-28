__kernel void complement( __global int *A,__global int *B)
{
	// Get the index of the current work item
	int tid = get_global_id(0);
	
	// Do the operation
	int num = A[tid];
	int pow=1,rem,bin=0;
	
	while (num!= 0) 
	{
        rem = num % 10;
      	
      	if (rem==0)
      		bin=bin+1*pow;
      	else
      		bin=bin+0*pow;
        pow = pow * 10;
        num /= 10;
    }
	B[tid]=bin;
}