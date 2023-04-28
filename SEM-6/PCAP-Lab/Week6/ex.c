#include <stdio.h>
#include<time.h>
#include <CL/cl.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
    time_t start, end;
    start = clock();
    char tempstr[200];
//Initialize the input string
    int i;
    for(i=0; i<200; i++)
        tempstr[i]='A';
    tempstr[200]='\0';
    int len= strlen(tempstr);
    len++;
    char *str = (char*)malloc(sizeof(char)*len);
    strcpy(str,tempstr);
// Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
    fp = fopen("ex.cl", "r");
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
    cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,len*sizeof(char), NULL, &ret);
// Copy the input string into respective memory buffer
    ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0,len *sizeof(char), str, 0, NULL, NULL);
// Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);
// Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
// Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "str_chgcase", &ret);
// Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);
// Set the global work size as string length
    size_t global_item_size = len; // Process the entire lists
    size_t local_item_size =1;
//Execute the OpenCL kernel for entire string in parallel
    cl_event event;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL, &event);
    time_t stime=clock();
//kernel execution must be finished before calculating time
    ret = clFinish(command_queue);
    cl_ulong time_start, time_end;
    double total_time;
//Find the kernel execution start time
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,sizeof(time_start), &time_start, NULL);
//Find the kernel execution end time
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,sizeof(time_end), &time_end, NULL);
    total_time = (double) (time_end - time_start);
// Read the result in memory buffer on the device to the local variable strres
    char *strres = (char*)malloc(sizeof(char)*len);
    ret = clEnqueueReadBuffer(command_queue, t_mem_obj, CL_TRUE, 0,len*sizeof(char), strres, 0, NULL, NULL);
    printf("\nDone");
    strres[len-1]='\0';
    printf("\nResultant toggled string :%s",strres);
    getchar();
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(s_mem_obj);
    ret = clReleaseMemObject(t_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    end = clock();
    printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3fmsec\n\n", total_time/1000000);
    printf( "\nTime taken to execute the whole program in seconds: %0.3fSeconds\n", (end-start)/(double)CLOCKS_PER_SEC );
    free(str);
    free(strres);
    return 0;
}
