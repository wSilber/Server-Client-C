#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define OK 0
#define NOT_OK 1

struct sockaddr_in server_addr, client_addr;
//struct addrinfo server_addr_info, cliend_addr_info;

int main(int argc, char * * argv)
{

	int server_fd;
	int sockfd, client_socket;
	int port;
	int backlog = 50;
	int bufferSize = 1028;
	ssize_t message_received;

	char buffer[bufferSize];

	/* Create socket */	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		return (NOT_OK);
	}

	port = atoi(argv[1]);

	server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port        = htons(port);

	/* Bind port number to the socket */
	if(bind(sockfd, (struct sockaddr * ) & server_addr, sizeof(server_addr)) < 0)
	{

		perror("Bind failed");
		return (NOT_OK);

	}

	printf("Done with binding with IP: %s, Port: %d\n", "127.0.0.2", port);

	/* Listen for connections */
	if(listen(sockfd, backlog) == -1)
	{
		perror("Error listening");
		return (NOT_OK);	
	}

	printf("Listening on port %d... \n", port);

	while(1)
	{
		socklen_t client_addr_size = sizeof(client_addr);
		if(client_socket = accept(sockfd, (struct sockaddr * ) & client_addr, & client_addr_size) == 1)
			{
				perror("Error accepting");
				return (NOT_OK);
			}

		message_received = recv(sockfd, buffer, bufferSize, 0);

		printf("Client: %s \n", buffer);

		memset(buffer, 0, bufferSize);

		strcpy(buffer, "Message from Server!");
		printf("Server: %s", buffer);

		send(sockfd, buffer, bufferSize, 0);

		close(client_socket);
	}

return (OK);

}
