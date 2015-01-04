#include "unp.h"

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0)
        Writen(sockfd, buf, n);

    if (n < 0 && errno == EINTR) {
        goto again;
    }
    else if (n < 0) {
        err_sys("str_echo: read error");
    }
}


int main(int argc, char* argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    struct sockaddr_in servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for (;;) {
        connfd = Accept(listenfd, 0, 0);
        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }

        Close(connfd);
    }


    return 0;
}


