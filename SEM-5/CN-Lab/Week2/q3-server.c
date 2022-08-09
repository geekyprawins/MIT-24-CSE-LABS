#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORTNO 10203

int sockfd, newsockfd, portno, clilen, n = 1, arr[5];
struct sockaddr_in seraddr, cliaddr;
int i, value;

void createServerSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
}

void performServerTask()
{
    while (1)
    {
        printf("Server Waiting\n");
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (fork() == 0)
        {
            n = read(newsockfd, arr, sizeof(arr));
            for (int i = 3; i >= 0; i--)
            {
                for (int j = 0; j <= i; j++)
                    if (arr[j] > arr[j + 1])
                    {
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
            }
            n = write(newsockfd, arr, sizeof(arr));
            close(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    }
}

int main()
{
    createServerSocket();
    performServerTask();
    return 0;
}