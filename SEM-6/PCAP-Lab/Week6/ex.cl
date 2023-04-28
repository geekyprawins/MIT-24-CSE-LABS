__kernel void str_chgcase (global char *A,global char *B)
{
	int i = get_global_id(0);
	
	if(A[i] >='A' && A[i] <='Z')
		B[i] = A[i] + 32;
	else
		B[i] = A[i] - 32;
}