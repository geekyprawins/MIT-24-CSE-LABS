#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10201

int sock, addrlen, client_fd, valread;
struct sockaddr_in address;
char buffer[1024] = {0};

void CreateClientSocket()
{
    // client socket creation
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    addrlen = sizeof(address);
}

void PerformClientTask()
{
    // connect client socket to the server socket
    client_fd = connect(sock, (struct sockaddr *)&address, addrlen);
    if (client_fd == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("Enter the string: ");
    memset(buffer, 0, sizeof(buffer));
    scanf("%s", buffer);
    send(sock, buffer, strlen(buffer), 0);
    printf("Message sent.\n");
    valread = read(sock, buffer, 1024);
    printf("Message echoed back: ");
    printf("%s\n", buffer);
}

int main()
{
    CreateClientSocket();
    PerformClientTask();
    close(client_fd);

    return 0;
}