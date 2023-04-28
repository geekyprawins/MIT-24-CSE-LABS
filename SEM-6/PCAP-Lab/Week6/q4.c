
#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>
//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
	// Create the two vectors
	int i,j;
	int LIST_SIZE,n;


	char S[100];
	printf("Enter string: ");
	fgets(S,100,stdin);
	LIST_SIZE = strlen(S);

	// char *B = (int*)malloc(sizeof(char)*LIST_SIZE*n);
	int pos[10];
	pos[0] = 0;
	j=1;
	for(i=0;i<LIST_SIZE;i++)
	{
		if(S[i] == ' ')
		{
			pos[j++] = i-1;
			pos[j++] = i+1;
		}
	}
	pos[j++] = LIST_SIZE - 1;



	
	// Load the kernel source code into the array source_str
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("q4.cl", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );
	
	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id, &ret_num_devices);
	
	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	
	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
	
	// Create memory buffers on the device for each vector A, B 
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,LIST_SIZE * sizeof(char), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,j * sizeof(int), NULL, &ret);
	
	// Copy the lists A to its respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(char), S, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,j * sizeof(int), pos, 0, NULL, NULL);

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t *)&source_size, &ret);
	
	// Build the program

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	// Create the OpenCL kernel object
	cl_kernel kernel = clCreateKernel(program, "reverse", &ret);
	
	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);

	// ret = clSetKernelArg(kernel, 2, sizeof(int), &LIST_SIZE);
	
	// Execute the OpenCL kernel on the array
	size_t global_item_size = j/2;
	size_t local_item_size = 1;
	
	//Execute the kernel on the device
	cl_event event;
	

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	ret = clFinish(command_queue);
	
	// Read the memory buffer C on the device to the local variable C
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(char), S, 0, NULL, NULL);
	
	// Display the result to the screen
	// S[LIST_SIZE] = '\0';
	printf("%s\n",S);
	
	// Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj); 
	ret = clReleaseCommandQueue(command_queue); 
	ret = clReleaseContext(context);


	return 0;

}


// output

 

