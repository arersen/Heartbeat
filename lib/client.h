//
// Created by waflek on 02.09.2025.
//

#ifndef HEARTBEAT_CLIENT_H
#define HEARTBEAT_CLIENT_H

#include "socket.h"

#ifdef _WIN32
#define SOCKETTYPE SOCKET
#else
#include <malloc.h>
#define SOCKETTYPE int
#endif
SOCKETTYPE client_init();
int client_connect(SOCKETTYPE sock);
void client_close(SOCKETTYPE sock);
void client_receive(SOCKETTYPE sock);
void client_send(SOCKETTYPE sock, const char* data, uint16_t size);

#endif //HEARTBEAT_CLIENT_H