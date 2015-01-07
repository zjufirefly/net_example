#include "unp.h"

void str_cli(FILE* fp, int sockfd)
{
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));
        if (Readline(sockfd, recvline, MAXLINE) == 0) {
            err_quit("str_cli: server terminate prematurely");
        }

        Fputs(recvline, stdout);
    }
}

int main(int argc, char* argv[])
{
    struct sockaddr_in servaddr;
    int sockfd;

    if (argc != 2) {
        err_quit("usage: client <IPaddress>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1],&servaddr.sin_addr);

    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    return 0;
}
