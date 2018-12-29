/**
 * test_makeproxyrequest.c
 */
#include<stdio.h>
#include"csapp.h"

#define DEBUG

#ifdef DEBUG
    #define dbg_printf(...) printf(__VA_ARGS__)
#else
    #define dbg_printf(...)
#endif

/* Function macros */
#define FORWARD_HDR(str) (!strstr(str, "Host:")&& !strstr(str,"User-Agent:")&&\
    !strstr(str, "Connection:")&& !strstr(str, "Proxy-Connection:"))

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

/*
 * parse_uri - parse URI into filename and CGI args
 *      What does request look like?
 *      What I do is to forward the original request to server, so I have to
 *          complete the request.
 */
/* $begin parse_uri */
void parse_uri(char* uri, char* hostname, char* port, char* filename)
{
    dbg_printf("***in parse_uri***\n");
    char *host_begin, *port_begin, *host_end;

    host_begin = strstr(uri, "://");    // uri in format "http://..."
    host_begin = (host_begin == NULL) ? uri : 
        host_begin + strlen("://"); 

    port_begin = index(host_begin, ':');

    host_end = index(host_begin, '/');  // uri in format "http://.../"
    host_end = (host_end == NULL) ? uri + strlen(uri) : host_end;

    port_begin = (port_begin == NULL) ? host_end : 
        port_begin + 1;  // uri in format "http://...:.../"

    strncpy(hostname, host_begin, host_end - host_begin);   // parse out hostname
    dbg_printf("hostname: %s\n", hostname);

    if(host_end - port_begin != 0)
        strncpy(port, port_begin, host_end - port_begin);
    else
        strcpy(port, "80");
    dbg_printf("port: %s\n", port);

    strcpy(filename, host_end);
    dbg_printf("filename: %s\n", filename);
}
/* $end parse_uri */

/*
 * read_requesthdrs - read HTTP request headers, and can just ignore them
 */
/* $begin read_requesthdrs */
void read_requesthdrs(rio_t *rp, char* original_hdr) 
{
    dbg_printf("***in read_requesthdrs***\n");

    char buf[MAXLINE];
    strcpy(original_hdr, "");
    dbg_printf("original_hdr = \n%s\n", original_hdr);
    Rio_readlineb(rp, buf, MAXLINE);
    dbg_printf("%s", buf);
    if(FORWARD_HDR(buf)){
        strcat(original_hdr, buf);
    }
    while(strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
        if(FORWARD_HDR(buf)){
            strcat(original_hdr, buf);
        }   
        dbg_printf("1 %s", buf);
    }
    return;
}
/* $end read_requesthdrs */

/**
 * make_proxy_request - form a HTTP request and HTTP header
 */
/* $begin make_proxy_request */
void make_proxy_request(char* request, char* HTTP_line, 
    char* hostname, char* original_hdr)
{
    dbg_printf("***in make_proxy_request***\n");
    memset(request, 0, MAXLINE);
    /* Make HTTP request line */
    strcpy(request, HTTP_line);
    /* Make HTTP request header */
    strcat(request, "Host: ");
    strcat(request, hostname);
    strcat(request, "\r\n");
    strcat(request, user_agent_hdr);
    strcat(request, "Connection: close\r\nProxy-Connection: close\r\n");
    strcat(request, original_hdr);
    strcat(request, "\r\n");
    dbg_printf("%s", request);
}
/* $end make_proxy_request */

int main(int argc, char** argv){
    int cnt = 3;
    rio_t rio;
    Rio_readinitb(&rio, STDIN_FILENO);
    while(cnt--){
        dbg_printf("cnt = %d\n", cnt);
        char original[MAXLINE], proxyreq[MAXLINE];
        char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
        char hostname[MAXLINE], port[MAXLINE], filename[MAXLINE];

        if (!Rio_readlineb(&rio, buf, MAXLINE))  //line:netp:doit:readrequest
            exit(0);
        dbg_printf("%s", buf);
        sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
        dbg_printf("original = \n%s\n", original);
        read_requesthdrs(&rio, original);
        parse_uri(buf, hostname, port, filename);
        make_proxy_request(proxyreq, buf, hostname, original);
    }
    exit(0);
}
