#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10503

int sock, addrlen, client_fd, valread;
struct sockaddr_in address;
int numbers[3] = {0};
char result[100] = {0};

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

    // memset(numbers, 0, sizeof(numbers));
    printf("Enter first operand: ");
    scanf("%d", &(numbers[0]));

    printf("1: +\n2: -\n3. *\n4. /\nEnter choice: ");
    scanf("%d", &(numbers[1]));

    printf("Enter second operand: ");
    scanf("%d", &(numbers[2]));

    send(sock, numbers, sizeof(numbers), 0);
    printf("Opeartors and Operands sent.\n");

    valread = read(sock, &result, sizeof(result));

    printf("%s\n", result);
}

int main()
{
    CreateClientSocket();
    PerformClientTask();
    close(client_fd);

    return 0;
}