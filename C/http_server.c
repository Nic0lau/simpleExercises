/* Simple HTTP Server */
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256
#define PORT 42069
#define IP_ADDR "127.0.0.1"
#define LISTEN_BACKLOG 5

int
main(int argc, char **argv)
{
	char buf[BUF_SIZE] = {'\0'};
	int sfd, cfd, client_addr_sz;
	struct sockaddr_in server_addr, client_addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		perror("[-] Error opening socket");
		return -1;
	}
	puts("[+] Socket sucessfully created.");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_aton(IP_ADDR, &server_addr.sin_addr);
	
	if (bind(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("[-] Error binding socket");
		return -1;
	}
	puts("[+] Socket sucessfully binded.");

	if (listen(sfd, LISTEN_BACKLOG) < 0) {
		perror("[-] Error listening");
		return -1;
	}
	puts("[+] Socket is listening...");
	
	strcpy(buf, "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\nContent-length: 5\r\n\r\nteste");
	while(1) {
		client_addr_sz = sizeof(client_addr);
		cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_addr_sz);
		if (cfd < 0) {
			perror("[-] Error accepting client");
			continue;
		}
		/* TODO: Print ipv4 address in dotted form */
		printf("[+] Sucessfully accepted client %d : %d\n", client_addr.sin_addr.s_addr, client_addr.sin_port);
		
		if (send(cfd, buf, strlen(buf), 0) < 0)
			perror("[-] Error sending message to client");
		else
			puts("[+] Sucessfully sent message to client.");
		
		printf("Disconnecting from client %d : %d\n", client_addr.sin_addr.s_addr, client_addr.sin_port);
		close(cfd);
	}

	close(sfd);
	return 0;
}
