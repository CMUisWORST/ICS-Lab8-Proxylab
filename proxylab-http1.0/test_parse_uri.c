/**
 * test_parse_uri.c
 * test function parse_uri
 */
#include<stdio.h>
#include"csapp.h"

#define DEBUG

#ifdef DEBUG
    #define dbg_printf(...) printf(__VA_ARGS__)
#else
    #define dbg_printf(...)
#endif


// /*
//  * parse_uri - parse URI into filename and CGI args
//  *      What does request look like?
//  *      What I do is to forward the original request to server, so I have to
//  *          complete the request.
//  */
// /* $begin parse_uri */
// void parse_uri(char* uri, char* hostname, char* port, char* filename)
// {
//     dbg_printf("***in parse_uri***");

//     char *host_begin, *port_begin, *host_end;

//     host_begin = strstr(uri, "://");    // uri in format "http://..."
//     host_begin = (host_begin == NULL) ? uri : 
//         host_begin + strlen("://"); 

//     port_begin = index(host_begin, ':');

//     host_end = index(host_begin, '/');  // uri in format "http://.../"
//     host_end = (host_end == NULL) ? uri + strlen(uri) : host_end;

//     port_begin = (port_begin == NULL) ? host_end : 
//         port_begin + 1;  // uri in format "http://...:.../"

//     strncpy(hostname, host_begin, port_begin - host_begin - 1);// parse hostname
//     dbg_printf("hostname: %s\n", hostname);

//     if(host_end - port_begin != 0)
//         strncpy(port, port_begin, host_end - port_begin);
//     else
//         strcpy(port, "80");
//     dbg_printf("port: %s\n", port);

//     strcpy(filename, host_end);
//     dbg_printf("filename: %s\n", filename);
// }
// /* $end parse_uri */

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

    port_begin = (port_begin == NULL) ? host_end + 1 : 
        port_begin + 1;  // uri in format "http://...:.../"

    strncpy(hostname, host_begin, port_begin - host_begin - 1);//parse hostname
    dbg_printf("hostname: %s\n", hostname);

    if(host_end - port_begin > 0)
        strncpy(port, port_begin, host_end - port_begin);
    else
        strcpy(port, "80");
    dbg_printf("port: %s\n", port);

    strcpy(filename, host_end);
    if(!strcmp(filename, "")){
        strcat(filename, "/");
    }
    dbg_printf("filename: %s\n", filename);
}
/* $end parse_uri */

/**
 * main - test parse_uri
 */
/* $begin main */
int main(int argc, char** argv){
    char buf[MAXLINE];
    char hostname[MAXLINE], filename[MAXLINE], port[MAXLINE];
    while(1){
        memset(hostname, 0, sizeof(hostname));
        memset(filename, 0, sizeof(filename));
        memset(port, 0, sizeof(port));
        scanf("%s", buf);
        if(!strcmp(buf, "exit")) exit(0);
        parse_uri(buf, hostname, port, filename);
    }
}
/* $end main */