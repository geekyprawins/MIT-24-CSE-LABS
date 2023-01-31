#include <stdio.h>
#include <stdlib.h>
#define frame 3
typedef struct queue
{
    int a[frame];
    int front;
    int rear;
} queue;

int isFull(queue *q)
{
    return (q->rear + 1) % frame == q->front;
}
int isEmpty(queue *q)
{
    return (q->rear == q->front);
}
void initialise(queue *q)
{
    q->front = -1;
    q->rear = -1;
}
void display(queue *q)
{
    for (int i = q->front; i != q->rear; i = (i + 1) % frame)
        printf("%d  ", q->a[i]);
    printf("%d  ", q->a[q->rear]);
}
void pop(queue *q)
{
    q->front = (q->front + 1) % frame;
}
void push(queue *q, int ele)
{
    if (isFull(q))
    {
        pop(q);
        push(q, ele);
        return;
    }
    if (isEmpty(q))
    {
        q->rear = (q->rear + 1) % frame;
        q->front = 0;
        q->a[q->rear] = ele;
        return;
    }
    q->rear = (q->rear + 1) % frame;
    q->a[q->rear] = ele;
}
void fifo(queue *q, int arr[], int n)
{
    int fault = 0;
    for (int i = 0; i < n; i++)
    {
        int fl = 0;
        for (int j = q->front; j != q->rear; j = (j + 1) % frame)
        {
            if (arr[i] == q->a[j])
            {
                display(q);
                printf("H\n");
                fl = 1;
            }
        }
        if (arr[i] == q->a[q->rear])
        {
            display(q);
            printf("H\n");
            fl = 1;
        }
        if (fl == 0)
        {
            push(q, arr[i]);
            display(q);
            printf("F\n");
            fault++;
        }
    }
    printf("No. of faults=%d\n", fault);
}
void displayarr(int arr[])
{
    for (int i = 0; i < frame; i++)
    {
        printf("%d  ", arr[i]);
    }
}
void LRU(int arr[], int n)
{
    int frames[frame], timer[frame], faults = 0;
    int time = 0;
    int ctr = 0;
    for (int i = 0; i < n; i++)
    {
        int fl = 0;
        for (int j = 0; j < ctr; j++)
        {
            if (arr[i] == frames[j])
            {
                timer[j] = time++;
                fl = 1;
                displayarr(frames);
                printf("H\n");
            }
        }
        if (fl == 0)
        {
            int min = 1000, ind = ctr;
            if (ctr == frame)
            {
                for (int j = 0; j < ctr; j++)
                {
                    if (timer[j] < min)
                    {
                        min = timer[j];
                        ind = j;
                    }
                }
            }
            timer[ind] = time++;
            frames[ind] = arr[i];
            if (ctr < frame)
                ctr++;
            displayarr(frames);
            printf("F\n");
            faults++;
        }
    }
    printf("No. of faults=%d\n", faults);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void optimal(int arr[], int n)
{
    int frames[frame], ctr = 0, index[frame], fault = 0;
    for (int m = 0; m < frame; m++)
    {
        index[m] = 99999;
    }
    for (int i = 0; i < n; i++)
    {
        int fl = 0;
        for (int j = 0; j < ctr; j++)
        {
            if (frames[j] == arr[i])
            {
                fl = 1;
                displayarr(frames);
                printf("H\n");
            }
        }
        if (fl == 0)
        {
            int mx = 0, ind = 0;
            if (ctr < frame)
            {
                frames[ctr] = arr[i];
                ctr++;
                displayarr(frames);
                fault++;
                printf("F\n");
                continue;
            }
            for (int m = 0; m < frame; m++)
            {
                index[m] = 999;
            }
            for (int j = 0; j < ctr; j++)
            {
                for (int k = i + 1; k < n; k++)
                {
                    if (frames[j] == arr[k])
                    {
                        index[j] = min(k, index[j]);
                    }
                }
            }
            for (int j = 0; j < ctr; j++)
            {
                if (index[j] > mx)
                {
                    ind = j;
                    mx = index[j];
                }
            }
            frames[ind] = arr[i];
            displayarr(frames);
            fault++;
            printf("F\n");
        }
    }
    printf("No. of faults is %d", fault);
}
int main()
{
    printf("Enter size of input string\n");
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Enter input string\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    queue *q = malloc(sizeof(q));
    initialise(q);
    fifo(q, arr, n);
    LRU(arr, n);
    optimal(arr, n);
}