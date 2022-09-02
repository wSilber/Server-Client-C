#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 12345
#define BUFFER_SIZE 512

#define OK 0
#define NOT_OK 1

struct sockaddr_in server_addr;

int main(int argc, char * * argv)
{

	int client_fd;
	int client_socket;

	char buffer[BUFFER_SIZE];

	/* Create socket for client */	
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		return (NOT_OK);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	/* Connect to server */
	if(client_fd = connect(client_socket, 
						   (struct sockaddr * ) & server_addr, 
						   sizeof(server_addr)) < 0)
	{
		printf("Connection failed \n");
		return (NOT_OK);
	}

	printf("Connected to server. Write your message to server...\n");

	memset(buffer, '\0', BUFFER_SIZE);
	//strcpy(buffer, "HELLO FROM CLIENT.");
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("Buffer: %s \n", buffer);
	
	/* Send message to server */
	send(client_socket, buffer, BUFFER_SIZE, 0);

	memset(buffer, '\0', BUFFER_SIZE);

	/* Wait for response from server */
	recv(client_socket, buffer, BUFFER_SIZE, 0);

	printf("Server: %s\n", buffer);

	/* Disconnect from server */
	close(client_socket);
return (OK);

}
