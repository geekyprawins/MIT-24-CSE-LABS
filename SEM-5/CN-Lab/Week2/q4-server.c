#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10503

int server_fd, new_socket, addrlen, valread, i, j;
struct sockaddr_in address;
int numbers[3] = {0};
float result = 0;
char msg[100];

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
            valread = read(new_socket, numbers, sizeof(numbers));

            // Perform operation
            if (numbers[1] == 1)
                result = numbers[0] + numbers[2];

            else if (numbers[1] == 2)
                result = numbers[0] - numbers[2];

            else if (numbers[1] == 3)
                result = (numbers[0]) * (numbers[2]);

            else if (numbers[1] == 4)
                result = (numbers[0]) / (numbers[2]);

            printf("\nOpeartion performed.\n");

            printf("Result calculated: %0.2f\n", result);

            // putting the result of opeartion in a string buffer
            memset(msg, 0, sizeof(msg));
            sprintf(msg, "The result of the operation is: %0.2f", result);

            // send this string buffer to the client
            send(new_socket, &msg, sizeof(msg), 0);

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