#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORTNO 9091

int sockfd, newsockfd, portno, clilen, n = 1;
struct sockaddr_in seraddr, cliaddr;
int i, value;

void CreateServerSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.57.93");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct socaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
}
void PerformServerTask()
{
    while (1)
    {
        char buf[256];
        printf("Server waiting");
        // Accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        n = read(newsockfd, buf, sizeof(buf));
        printf(" \nMessage from Client %s \n", buf);
        n = write(newsockfd, buf, sizeof(buf));
    }
}

int main()
{
    CreateServerSocket();
    PerformServerTask();

    return 0;
}