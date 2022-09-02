#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 512
#define PORT 12345

#define OK 0
#define NOT_OK 1

struct sockaddr_in server_addr, client_addr;

int main(void)
{

	/* Server/ Client socket handles */
	int server_socket, client_socket;

	/* Amount of queued connections allowed */
	int backlog = 1;

	/* Buffer to hold message for sending/ receiving */
	char buffer_client[BUFFER_SIZE];
	char buffer_server[BUFFER_SIZE];

	/* Create socket */	
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		return (NOT_OK);
	}

	server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port        = htons(PORT);

	/* Bind port number to the socket */
	if(bind(server_socket, (struct sockaddr * ) & server_addr, sizeof(server_addr)) < 0)
	{

		perror("Bind failed");
		return (NOT_OK);

	}

	printf("Done with binding with IP: %s, Port: %d\n", "127.0.0.1", PORT);

	/* Listen for connections */
	if(listen(server_socket, backlog) == -1)
	{
		perror("Error listening");
		return (NOT_OK);	
	}

	memset(buffer_client, 0, BUFFER_SIZE);

	socklen_t client_addr_size = sizeof(client_addr);

	if((client_socket = accept(server_socket, 
							  (struct sockaddr * ) & client_addr,
							  & client_addr_size)) < 0)
		{
			perror("Error accepting");
			return (NOT_OK);
		}

	int client_ip = client_addr.sin_addr.s_addr;

	/* Parse client ip address and port */
	printf("Client connected at IP: %d.%d.%d.%d:%i\n", 
			client_ip & 0xFF,
			(client_ip >> 8) & 0xFF,
			(client_ip >> 16) & 0xFF,
			(client_ip << 24) & 0xFF,
			ntohs(client_addr.sin_port));

	printf("Client has connected\n");

	/* Receive message from client */	
	recv(client_socket, buffer_client, BUFFER_SIZE, 0);

	printf("Client: %s \n", buffer_client);
	memset(buffer_server, 0, BUFFER_SIZE);
	
	strcpy(buffer_server, "Received message from Client!");
	printf("Server: %s \n", buffer_server);
	
	/* Send server response to client */
	send(client_socket, buffer_server, BUFFER_SIZE, 0);
	
	/* Close connection to client */
	close(client_socket);

return (OK);

}
