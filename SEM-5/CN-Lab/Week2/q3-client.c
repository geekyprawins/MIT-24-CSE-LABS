#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORTNO 10203

int len, result, sockfd, n = 1, arr[5];
struct sockaddr_in address;
char ch[256], buff[256];

void createClientSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("CLIENT ERROR\n");
        exit(1);
    }
}

void performClientTask()
{
    printf("Enter the five elements in the array: ");
    for (int i = 0; i < 5; i++)
        scanf("%d", &(arr[i]));
    write(sockfd, arr, sizeof(arr));
    printf("Sorted array is: ");
    n = read(sockfd, arr, sizeof(arr));
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
}

int main()
{
    createClientSocket();
    performClientTask();
    return 0;
}