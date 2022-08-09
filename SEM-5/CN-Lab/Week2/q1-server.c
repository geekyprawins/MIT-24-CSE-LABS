#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10201

int server_fd, new_socket, addrlen, valread;
struct sockaddr_in address;
char buffer[1024] = {0};

void CreateServerSocket()
{
    // create a welcome socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // server address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORTNO);
    addrlen = sizeof(address);
}

void PerformServerTask()
{
    // bind the welcome socket to the local protocol address
    bind(server_fd, (struct sockaddr *)&address, addrlen);

    // make welcome socket wait for a client request;
    printf("Server Waiting....\n");
    listen(server_fd, 5);

    // when client wants to establish connection
    while (1)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        if (fork() == 0)
        {
            valread = read(new_socket, buffer, 1024);
            send(new_socket, buffer, strlen(buffer), 0);
            printf("Message Recieved.\n");
            // closing the new socket created
            close(new_socket);
            exit(0);
        }
        else
            close(new_socket);
    }
}

int main()
{
    CreateServerSocket();

    PerformServerTask();

    // closing the welcoming socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}