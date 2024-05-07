#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<netdb.h>
#include <arpa/inet.h>
#include<netinet/in.h>


int main(int argc, char* argv[]) {
    int status;
    struct addrinfo* result, hint;
    struct sockaddr_in* tst;

    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    char addr[INET_ADDRSTRLEN];

    if ((status = getaddrinfo(NULL, "8000", &hint, &result)) !=0){
        printf("Got error\n");
        fprintf(stderr, "%s\n", gai_strerror(status));
        exit(1);
    }
    tst = (struct sockaddr_in*)result->ai_addr;
    printf("got addr\n");
    inet_ntop(AF_INET, &(tst->sin_addr), addr, INET_ADDRSTRLEN);
    printf("%s\n", addr);
    freeaddrinfo(result);
    return 0;
}