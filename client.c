//int socket(int domain, int type, int protocol);
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//int listen(int sockfd, int backlog);
//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//uint16_t htons(uint16_t hostshort);
//int atoi(const char *nptr);
//in_addr_t inet_addr(const char *cp);
//void bzero(void *s, size_t n);
//int listen(int sockfd, int backlog);
//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

#include <stdio.h>
#include <sys/types.h>//socket():bind();listen():accept();listen();accept();connect();
#include <sys/socket.h>//socket():bind();listen():accept();inet_addr();listen():accept();connect();
#include <arpa/inet.h>//htons();inet_addr():
#include <netinet/in.h>//inet_addr():
#include <strings.h>//bzero();
#include <stdlib.h>//atoi();exit();
#include <unistd.h>//close():
#include <string.h>

#define N 64

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Using: %s ip port\n",argv[0]);
        exit(-1);
    }
    int sockfd;
    struct sockaddr_in myaddr,peeraddr;
    char buf[N] = {0};
    size_t n;
    socklen_t mylen,peerlen;
    mylen = sizeof(myaddr);
    peerlen = sizeof(peeraddr);
    /*  creat socket  */
    if(-1 == (sockfd = socket(AF_INET,SOCK_DGRAM,0)))
    {
        perror("socket");
        exit(-1);
    }
    /* bind initialization */
    bzero(&myaddr,sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(argv[2])+1);
    myaddr.sin_addr.s_addr = inet_addr(argv[1]);
    /*      bind      */
    if(-1 == bind(sockfd, (struct sockaddr *)&myaddr, mylen))
    {
        perror("bind");
        exit(-1);
    }
    /*    connect    */
    bzero(&peeraddr, sizeof(peeraddr));
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(atoi(argv[2]));
    peeraddr.sin_addr.s_addr = inet_addr(argv[1]);
    //connect(sockfd,(struct sockaddr *)&peeraddr, peerlen);
    while(1){
    fgets(buf, N, stdin);
    printf("buf:%s",buf);
    if(-1 == (n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&peeraddr, peerlen)))
    {
        perror("sendto");
        exit(-1);
    }
    if(strncmp(buf, "quit", 4) == 0)
            break;
    printf("n = %d\n",n);
    }
    close(sockfd);
    exit(0);
}