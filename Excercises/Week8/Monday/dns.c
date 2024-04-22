#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(){
    printf("enter web address:");
    char *address = malloc(30);
    void *ptr;
    struct addrinfo hint, *result, *res;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    int ip;
    scanf("%s", address);
    ip = getaddrinfo(address, NULL, &hint, &result);
    printf("test\n");
    res = result;   
    while (res)
    {
        ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
        inet_ntop (res->ai_family, ptr, address, 100);
        printf ("IPv4 address: %s\n", address);
        res = res->ai_next;
    }
    return 0;
}