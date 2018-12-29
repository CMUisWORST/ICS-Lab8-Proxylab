/**
 * proxy.h - functions and macros in this project
 */

#ifndef __PROXY_H__
#define __PROXY_H__

#include "csapp.h"

/* Debug mode: type '#define DEBUG' blow */

#ifdef DEBUG
    #define dbg_printf(...) printf(__VA_ARGS__)
#else
    #define dbg_printf(...)
#endif

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 10490000     // approximately 10MB
#define MAX_OBJECT_SIZE 819200      // approximately 400KB
#define MAX_OBJ_NUM 2048            // 10MB / 5KB

/* Max file size */
#define MAX_FILE_SIZE 1049000

/* Function macros */
#define FORWARD_HDR(str) (!strstr(str,"User-Agent:")&&!strstr(str, "Host:")&&\
    !strstr(str, "Connection:")&& !strstr(str, "Proxy-Connection:"))

/* Global variables */
sem_t wtmutex, rdmutex;
int readcnt;

#endif