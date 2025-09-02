//
// Created by waflek on 02.09.2025.
//

#ifndef HEARTBEAT_CLIENT_H
#define HEARTBEAT_CLIENT_H

#include "socket.h"

SOCKET client_init();
int client_connect(SOCKET sock);
void client_close(SOCKET sock);
void client_receive(SOCKET sock);
void client_send(SOCKET sock, const char* data, uint16_t size);
#endif //HEARTBEAT_CLIENT_H