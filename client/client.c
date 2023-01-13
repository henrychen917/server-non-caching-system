#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT "88888"
#define DEFAULT_ADDR "192.168.50.80"

int main (int argc, char *argv[])
{
    int sockfd, len;
    char buf[BUFSIZ];
    struct sockaddr_in serv;
    int port;

    if ((sockfd = socket (PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    serv.sin_family = PF_INET;

    if (argc == 3) {
        port = strtol(argv[2], NULL, 10);
    } else {
        port = strtol(DEFAULT_PORT, NULL, 10);
    }
    serv.sin_port = htons(port);

    if (argc >= 2){
        inet_aton(argv[1], &serv.sin_addr);
    }else{
        inet_aton(DEFAULT_ADDR, &serv.sin_addr);
    }
    if (connect (sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }
    while (strncasecmp(buf, "Client exited", 13) != 0) {
        printf("==> ");
        if((fgets (buf, BUFSIZ, stdin)) < 0) {
            perror("fgets");
        }
        len = send (sockfd, buf, strlen(buf), 0);
        len = recv (sockfd, buf, 200, 0);
        buf[len] = '\0';
        printf("<== %s\n", buf);
    }
    close (sockfd);
    return 0;
}