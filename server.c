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
    struct sockaddr_storage their_data;
    int status, sock, new_sock, yes = 1;

    memset(&hints, 0, sizeof hints);

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(NULL, "8000", &hints, &res) != 0))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return status;
    }

    if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
        fprintf(stderr, "socket: %s\n", strerror(errno));
        return 1;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
    {
        perror("setsockopt");
        return 1;
    }

    if (bind(sock, res->ai_addr, res->ai_addrlen) == -1)
    {
        fprintf(stderr, "bind: %s\n", strerror(errno));
        return 1;
    }

    if (listen(sock, BACKLOG) == -1)
    {
        fprintf(stderr, "listen: %s\n", strerror(errno));
        return 1;
    }

    printf("Accepting conn\n");

    while (1)
    {
        socklen_t addr_size = sizeof their_data;
        if ((new_sock = accept(sock, (struct sockaddr *)&their_data, &addr_size)) == -1)
        {
            fprintf(stderr, "accept: %s\n", strerror(errno));
            return 1;
        }
        printf("got request\n");

        char *msg = "Hello, world!";
        int bytes_sent, msg_len = strlen(msg);

        bytes_sent = send(new_sock, msg, msg_len, 0);

        printf("Bytes send: %d\n", bytes_sent);
    }
}