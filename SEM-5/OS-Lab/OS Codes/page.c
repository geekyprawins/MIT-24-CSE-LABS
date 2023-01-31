int min(int a, int b)
{
    return a < b ? a : b;
}

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
}