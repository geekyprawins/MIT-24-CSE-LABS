#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 10053
#define MAXLINE 1000
// Client code
int main()
{
    char buffer[100];
    int sockfd, n, len;
    struct sockaddr_in servaddr, cliaddr;
    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    char buff[100];
    for (;;)
    {
        bzero(buff, sizeof(buff));
        printf("Enter The Elements of the Matrix Row : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        buff[n] = '\0';
        sendto(sockfd, &buff, MAXLINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("Closing client\n");
            break;
        }
        bzero(buff, sizeof(buff));
        len = sizeof(cliaddr);
    }
    // close the descriptor
    close(sockfd);
}