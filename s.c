#include <stdio.h>
#include <sys/socket.h>

int main (int argc, char *argv[]) {
	int socketDesc = socket (AF_INET, SOCK_STREAM, 0);

	if (socketDesc == -1) {
		printf ("Failed to create socket!");
		return  0;
	}
	printf("Success!\n");
	return 0;
}
