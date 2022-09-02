#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1028

struct sockaddr_in server_addr;

int main(int argc, char * * argv)
{

	int client_fd;
	int client_socket;
	char buffer[BUFFER_SIZE];
	
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		return 1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(5000);

	connect(client_socket, (struct sockaddr * ) & server_addr, sizeof(server_addr));

	printf("Connected to server.\n");

	strcpy(buffer, "Message from Client!");
	printf("Buffer: %s \n", buffer);
	send(client_socket, buffer, strlen(buffer), 0);

return 0;

}
