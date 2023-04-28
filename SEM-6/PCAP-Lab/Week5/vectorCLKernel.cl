__kernel void vector_add(__global int *A, __global int *B, __global int *C)
{

    // Get index of current work item
    int i = get_global_id(0);
    // Do the operation
    C[i] = A[i] + B[i];
}