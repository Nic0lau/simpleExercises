#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_LEN 8192

int
main(int argc, char **argv)
{
	struct addrinfo *info, hints;
	int gai_status, recv_status, sfd;
	char buf[BUF_LEN];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [website]\n", argv[0]);
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((gai_status = getaddrinfo(argv[1], "http", &hints, &info)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_status));
		return -1;
	}

	for (;info;info = info->ai_next) {
		if ((sfd = socket(info->ai_family, info->ai_socktype, 0)) < 0) {
			perror("socket");
			continue;
		}

		if (connect(sfd, info->ai_addr, info->ai_addrlen) < 0) {
			perror("connect");
			continue;
		}

		break;	
	}

	send(sfd, "GET / HTTP/1.0\r\n\r\n", 19, 0);

	while(1) {
		memset(buf, 0, sizeof(buf));
		if ((recv_status = recv(sfd, buf, sizeof(buf), 0)) > 0) {
			printf("%s", buf);
		} else if (recv_status == 0) {
			break;
		} else {
			perror("recv");
			break;
		}
	}

	putchar('\n');
	freeaddrinfo(info);
	close(sfd);

	return 0;
}
