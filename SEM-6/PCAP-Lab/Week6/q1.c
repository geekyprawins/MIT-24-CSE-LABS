#include <stdio.h>
#include<time.h>
#include <CL/cl.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
    char str[200];
    char *res;
    int n;
//Initialize the input string
    int i;
    printf("Input String:\n");
    gets(str);
    int len= strlen(str);
    printf("Enter n:\n");
    scanf("%d",&n);

    res = malloc(sizeof(char)*len*n);
   
    
// Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
    fp = fopen("q1.cl", "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        getchar();
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;

    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,&ret_num_devices);

// Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

// Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context,device_id, CL_QUEUE_PROFILING_ENABLE, &ret);

// Create memory buffers on the device for input and output string  
    cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,len*sizeof(char), NULL, &ret);
    cl_mem res_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,len*sizeof(char)*n, NULL, &ret);

// Copy the input string into respective memory buffer
    ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0,len *sizeof(char), str, 0, NULL, NULL);

// Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);

// Build the program
    printf("Host error code: %d\n",ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    printf("Kernel error code: %d\n",ret);

// Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "strCpy", &ret);

// Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&res_mem_obj);
    ret = clSetKernelArg(kernel,2,sizeof(int),&len);

// Set the global work size as string length
    size_t global_item_size = n; // Process the entire lists
    size_t local_item_size =1;

//Execute the OpenCL kernel for entire string in parallel
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL,NULL);
  
// Read the result in memory buffer on the device to the local variable strres
    ret = clEnqueueReadBuffer(command_queue, res_mem_obj, CL_TRUE, 0,len*sizeof(char)*n,res, 0, NULL, NULL);
    res[len*n]='\0';
    printf("\nResultant concatenated string :%s\n",res);
    getchar(); 

    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(s_mem_obj);
    ret = clReleaseMemObject(res_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(res);
    return 0;
}
