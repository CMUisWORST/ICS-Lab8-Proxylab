/**
 * mylib.h - functions in mylib.c
 */
#ifndef __MYLIB_H__
#define __MYLIB_H__

#include "proxy.h"

int my_open_listenfd(char *port);
int my_open_clientfd(char *hostname, char *port);

#endif