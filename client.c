#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

const int BACKLOG = 20;

int main(int argc, char *argv[])
{
    struct addrinfo hints, *res;
    int status, sock, new_sock, yes = 1;
    char buf[100];

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("localhost", "8000", &hints, &res) != 0))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return status;
    }

    if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        fprintf(stderr, "socket: %s\n", strerror(errno));
        return 1;
    }

    if (connect(sock, res->ai_addr, res->ai_addrlen) == -1)
    {
        fprintf(stderr, "socket: %s\n", strerror(errno));
        return 1;
    }

    size_t bsize = sizeof buf;
    recv(sock, buf, bsize, 0);

    printf("%s\n", buf);

}