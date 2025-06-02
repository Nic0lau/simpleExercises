#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>

int
main(int argc, char **argv)
{
	char addr[INET6_ADDRSTRLEN];
	struct addrinfo *info;
	struct sockaddr_in *ipv4;
	struct sockaddr_in6 *ipv6;
	int status;

	if (argc != 2) {
		printf("Usage: %s [host]\n", argv[0]);
		return -1;
	}

	if ((status = getaddrinfo(argv[1], NULL, NULL, &info)) != 0) {
		puts(gai_strerror(status));
		return -1;
	}

	for (;info->ai_next;info = info->ai_next) {
		if (info->ai_family == AF_INET) {
			ipv4 = (struct sockaddr_in *) info->ai_addr;
			inet_ntop(info->ai_family, &ipv4->sin_addr, addr, INET6_ADDRSTRLEN);
		} else {
			ipv6 = (struct sockaddr_in6 *) info->ai_addr;
			inet_ntop(info->ai_family, &ipv6->sin6_addr, addr, INET6_ADDRSTRLEN);
		}

		puts(addr);
	}

	freeaddrinfo(info);

	return 0;
}
