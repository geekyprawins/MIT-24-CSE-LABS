#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, testfds;
    // Create and name a socket for the server
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8000);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    // Create a connection queue and initialize readfds to handle input from server_sockfd
    listen(server_sockfd, 5);
    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    // Now wait for clients and requests. Because you have passed a null pointer as the timeout
    // parameter, no timeout will occur. The program will exit and report an error if select returns
    // a value less than 1
    while (1)
    {
        char ch;
        int fd, nread;
        testfds = readfds;
        printf("server waiting\n");
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        // After this time, test result. If there has been an error, the program exits:
        if (result < 1)
        {
            perror("server error");
            exit(1);
        }
        // Once you know you’ve got activity, you can find which descriptor it’s on by checking
        // each in turn using FD_ISSET
        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &testfds))
            {
                // If the activity is on server_sockfd, it must be a request for a new connection, and
                // you add the associated client_sockfd to the descriptor set:
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address,
                                           &client_len);
                    FD_SET(client_sockfd, &readfds);
                    printf("adding client on fd %d\n", client_sockfd);
                }
                // If it isn’t the server, it must be client activity. If close is received, the client has gone
                // away, and you remove it from the descriptor set. Otherwise, you “serve” the client
                // as in the previous examples.
                else
                {
                    ioctl(fd, FIONREAD, &nread);
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("removing client on fd %d\n", fd);
                    }
                    else
                    {
                        read(fd, &ch, 1);
                        sleep(5);
                        printf("serving client on fd %d\n", fd);
                        ch++;
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }
}
