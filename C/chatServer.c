#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "chatConnection.h"

#define LISTEN_BACKLOG 5

int main()
{
	unlink(SERVER_PATH);
	
	struct sockaddr_un serverSocketAddress, clientSocketAddress;
	int clientSocketHandler, serverSocketHandler;
	socklen_t clientSocketAddressLength;
	char buffer[BUFFER_SIZE];
	
	serverSocketAddress.sun_family = AF_UNIX;
	strcpy(serverSocketAddress.sun_path, SERVER_PATH);
	clientSocketAddress.sun_family = AF_UNIX;
	strcpy(clientSocketAddress.sun_path, CLIENT_PATH);
	clientSocketAddressLength = sizeof(clientSocketAddress);
	serverSocketHandler = socket(AF_UNIX,SOCK_STREAM, 0);
	
	if (bind(serverSocketHandler, (struct sockaddr *) &serverSocketAddress, sizeof(serverSocketAddress)) < 0) {
		perror("Binding error");
		return -1;
	};
	if (listen(serverSocketHandler, LISTEN_BACKLOG) < 0) {
		perror("Listening error");
		return -1;
	};
	for (;;) {
		clientSocketHandler = accept(serverSocketHandler, (struct sockaddr *) &clientSocketAddress, &clientSocketAddressLength); 
		if (read(clientSocketHandler, &buffer, sizeof(buffer)) < 0) {	
			perror("Error reading message from client");
		};
	
		printf("%s\n", buffer);
	};
	close(clientSocketHandler);
	close(serverSocketHandler);
	return 0;
};
