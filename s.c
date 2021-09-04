#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main (int argc, char *argv[]) {
	
	struct sockaddr_in server;
	int serverAddressLength = sizeof(server);
	int socketDescriptor = socket (AF_INET, SOCK_STREAM, 0); //Creating socket
	int requestHandlingSocket;
	
	char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 28\n\nGreetings from Ansh's server", serv_response[30000] = {0};
	
	long socketRead;

	if (socketDescriptor == -1) {
		printf ("Failed to create socket!\n");
		return  0;
	}
	
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	
	memset (server.sin_zero, '\0', sizeof(server.sin_zero));
	
	//Connecting to remote server
	if (bind(socketDescriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Error in bind!\n");
		return 1;
	}
	
	
	if (listen(socketDescriptor, 5) < 0) {
		printf("Listen failed!\n");
		return 1;
	}
	
	printf("Server listening\n");
	
	
	while(1) {
		
		printf("Waiting for new connection\n");
		
		if ((requestHandlingSocket = accept(socketDescriptor, (struct sockaddr *)&server, (socklen_t*)&serverAddressLength)) < 0) {
			printf("Accept failed!\n");
		}
		
		socketRead = read(requestHandlingSocket, serv_response, 30000);
		printf("%s\n", serv_response);
	
		write(requestHandlingSocket, message, strlen(message));
	
		printf("Greeting sent!\n");
		//Close the socket
		close (requestHandlingSocket);
		
	}
	
	close (socketDescriptor);
	
	return 0;
}
