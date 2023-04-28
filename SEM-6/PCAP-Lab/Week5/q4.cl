__kernel void binTodeci( __global int *A,__global int *B)
{
	// Get the index of the current work item
	int tid = get_global_id(0);
	
	// Do the operation
	int num = A[tid];
	int pow=1,rem,deci=0;
	
	while ( num > 0)  
    {  
        rem = num % 10; 
        deci= deci+ rem * pow;  
        num = num / 10; 
        pow = pow * 2;  
    } 
	B[tid]=deci;
}