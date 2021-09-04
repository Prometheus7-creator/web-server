#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]) {
	
	struct sockaddr_in server;
	
	//Creating socket
	int socketDescriptor = socket (AF_INET, SOCK_STREAM, 0);
	
	char *message, serv_response[2000];

	if (socketDescriptor == -1) {
		printf ("Failed to create socket!\n");
		return  0;
	}
	
	server.sin_addr.s_addr = inet_addr("142.251.33.110");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	
	//Connecting to remote server
	if (connect(socketDescriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Error in connection!\n");
		return 1;
	}
	
	printf("Connected\n");
	
	message = "GET / HTTP/1.1\r\n\r\n";
	
	if (send(socketDescriptor, message, strlen(message), 0) < 0) {
		printf("Send failed!\n");
		return 1;
	}
	
	printf("Data Sent\n");
	
	if (recv(socketDescriptor, serv_response, 2000, 0) < 0) {
		printf("Receive failed!\n");
	}
	
	printf("Response received\n");
	printf("%s\n", serv_response);
	
	//Close the socket
	close (socketDescriptor);
	
	printf("Socket closed.\n");
	
	return 0;
}
