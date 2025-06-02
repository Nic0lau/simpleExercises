#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>

int
main(int argc, char **argv)
{
	struct addrinfo *info;
	struct sockaddr_in *ipaddr4;
	struct sockaddr_in6 *ipaddr6;

	char ipaddress[INET6_ADDRSTRLEN];
	int gai_status;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [hostname]\n", argv[0]);
		return -1;
	}

	if ((gai_status = getaddrinfo(argv[1], NULL, NULL, &info)) != 0) {
		fprintf(stderr, "%s\n", gai_strerror(gai_status));
		return -1;
	}

	for (;info;info = info->ai_next) {
		memset(ipaddress, 0, sizeof(ipaddress));
		if (info->ai_family == AF_INET) {
			ipaddr4 = (struct sockaddr_in *) info->ai_addr;
			inet_ntop(info->ai_family, &ipaddr4->sin_addr, ipaddress, sizeof(ipaddress));
		} else {
			ipaddr6 = (struct sockaddr_in6 *) info->ai_addr;
			inet_ntop(info->ai_family, &ipaddr6->sin6_addr, ipaddress, sizeof(ipaddress));
		}
		printf("%s: %s\n", argv[1], ipaddress);
	}

	freeaddrinfo(info);

	return 0;
}
