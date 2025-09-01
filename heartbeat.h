//
// Created by waflek on 01.09.2025.
//

#ifndef HEARTBEAT_HEARTBEAT_H
#define HEARTBEAT_HEARTBEAT_H
#include <stdio.h>
#include <sys/types.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif


#include <string.h>
#include <stdio.h>
void test();

#ifdef _WIN32
SOCKET
#else
int
#endif
server_init();

#ifdef _WIN32
void close_server(SOCKET sock);
#else
void close_server(int socket);
#endif

#ifdef _WIN32
void server_poll(SOCKET sock);
#else
void server_poll(int sock);
#endif

#endif //HEARTBEAT_HEARTBEAT_H