#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "chatConnection.h"

int main()
{
	unlink(CLIENT_PATH);
	
	struct sockaddr_un clientSocketAddress, serverSocketAddress;
	int clientSocketHandler, serverSocketHandler;
	char buffer[BUFFER_SIZE];
	
	serverSocketAddress.sun_family = AF_UNIX;
	strcpy(serverSocketAddress.sun_path, SERVER_PATH);
	clientSocketAddress.sun_family = AF_UNIX;
	strcpy(clientSocketAddress.sun_path, CLIENT_PATH);
	serverSocketHandler = socket(AF_UNIX, SOCK_STREAM, 0);
	clientSocketHandler = socket(AF_UNIX, SOCK_STREAM, 0);
	
	puts("Digite sua mensagem:");
	fgets(&buffer, BUFFER_SIZE, stdin);
	
	if (connect(serverSocketHandler, (struct sockaddr *) &serverSocketAddress, sizeof(serverSocketAddress)) < 0) {
		perror("Connection error");
		return -1;
	};
	if (send(serverSocketHandler, &buffer, sizeof(buffer), 0) < 0) {
		perror("Error sending message");
		return -1;
	};
	for (;;) {};
	close(serverSocketHandler);
	close(clientSocketHandler);
	return 0;
};
