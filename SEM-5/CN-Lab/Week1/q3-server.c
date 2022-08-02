#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

void servfunc(int conn_fd, struct sockaddr_in client_address)
{
    // display client ip and port number
    // echo back received string in upper case
    // if quit is received from client/server, end program
    char buff[MAX];
    int n = 0;
    char *ip_add = inet_ntoa(client_address.sin_addr);
    int port = client_address.sin_port;
    printf("Client ip:%s Client port:%d \n", ip_add, port);
    while (1)
    {

        printf("Waiting from client...\n");
        // while(n==0)
        memset(buff, 0, sizeof(buff));
        n = read(conn_fd, buff, sizeof(buff));
        buff[n] = '\n';
        printf("Client ip:%s Client port:%d and msg recieved is %s \n", ip_add, port, buff);

        if (strcmp("quit", buff) == 0)
        {
            printf("Server is closing......closed\n");
            return;
        }

        for (int i = 0; i < n; i++)
        {
            buff[i] = toupper(buff[i]);
        }
        write(conn_fd, buff, sizeof(buff));
    }
}

int main()
{
    int server_sockfd, conn_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    // create a socket for the server

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // name the server socket
    server_address.sin_family = AF_INET;
    // inet_addr converts to unsigned long,
    // else use  htonl(INADDR_ANY)
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(7280);
    server_len = sizeof(server_address);

    if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) != 0)
    {
        printf("Socket binding failed\n");
        exit(0);
    }

    else
    {
        printf("Socket bound successfully\n");
    }

    // create a connection queue and wait for clients
    if (listen(server_sockfd, 2) != 0)
    {
        printf("Listen failed\n");
        exit(0);
    }

    else
    {
        printf("Server listening\n");
    }

    client_len = sizeof(client_address);
    // when accepted a new client, a new socketfd is created

    conn_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

    if (conn_sockfd < 0)
    {
        printf("Server accept failed\n");
        exit(0);
    }

    else
    {
        printf("Server accepted the client\n");
    }

    servfunc(conn_sockfd, client_address);

    close(server_sockfd);

    return 0;
}