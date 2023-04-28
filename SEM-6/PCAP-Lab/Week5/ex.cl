// vectorCLKernel.cl
__kernel void vector_add( __global int *A,__global int *B,__global int *C)
{
	// Get the index of the current work item
	int tid = get_global_id(0);
	// Do the operation
	C[tid] = A[tid] + B[tid];
}