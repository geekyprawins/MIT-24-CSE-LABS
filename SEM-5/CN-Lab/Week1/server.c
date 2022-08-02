#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORTNO 8080

int main()
{
	int sockfd, newsockfd, portno, clilen, n = 1;
	struct sockaddr_in seraddr, cliaddr;
	int i, value;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	seraddr.sin_port = htons(PORTNO);
	bind(sockfd, (struct socaddr *)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);

	while (1)
	{
		char buf[256];
		printf("server waiting");
		// Accept a connection
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

		n = read(newsockfd, buf, sizeof(buf));
		printf(" \nMessage from Client %s \n", buf);
		n = write(newsockfd, buf, sizeof(buf));
	}
}