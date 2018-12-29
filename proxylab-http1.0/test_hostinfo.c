#include"csapp.h"
int main(int argc, char** argv){
    struct addrinfo hints, *p, *listp;
    char buf[MAXLINE];
    int rc, flags;
    if(argc != 2){
        fprintf(stderr, "oho!\n");
        exit(0);
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0){
        fprintf(stderr, "oho!!\n");
        exit(1);
    }
    // flags = NI_NUMERICHOST;
    flags = 0;
    for(p = listp; p; p = p->ai_next){
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }
    Freeaddrinfo(listp);
    exit(0);
}