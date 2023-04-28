__kernel void dec_to_octal(__global int *A, __global int *C)
{

    // Get index of current work item
    int i = get_global_id(0);
    // Do the operation
    int a = 0, b = 1, n = A[i];
    
    while(n!=0){
        a += (n%8) * b;
        n/=8;
        b*=10;
    }

    C[i] = a;
}