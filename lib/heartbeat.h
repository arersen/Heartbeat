//
// Created by waflek on 01.09.2025.
//

#ifndef HEARTBEAT_HEARTBEAT_H
#define HEARTBEAT_HEARTBEAT_H
#include <stdio.h>
#include <sys/types.h>
#include <uuids.h>

#include <string.h>
#include <stdio.h>

#include "server.h"
#include "client.h"

void heartbeat(SOCKET sock);
void listen_heartbeat(SOCKET sock);
SOCKET heartbeat_init();

typedef struct {
    uuid_t uuid;
    SOCKET sock;
} Client;

void heartbeat_accept_thread(SOCKET sock, Client *clients, uint16_t* clients_count);
#endif //HEARTBEAT_HEARTBEAT_H