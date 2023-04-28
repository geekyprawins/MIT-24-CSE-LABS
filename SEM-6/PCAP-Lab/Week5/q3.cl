__kernel void adjSwap( __global int *A)
{
	// Get the index of the current work item
	int tid = get_global_id(0);
	
	// Do the operation
	int temp=A[2*tid];
	A[2*tid]=A[2*tid+1];
	A[2*tid+1]=temp;
	temp=0;
}