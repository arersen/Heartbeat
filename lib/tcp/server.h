//
// Created by waflek on 02.09.2025.
//

#ifndef HEARTBEAT_SERVER_H
#define HEARTBEAT_SERVER_H

#include "../socket.h"

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

#endif //HEARTBEAT_SERVER_H