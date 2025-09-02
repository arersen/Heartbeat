//
// Created by waflek on 01.09.2025.
//

#ifndef HEARTBEAT_HEARTBEAT_H
#define HEARTBEAT_HEARTBEAT_H
#include <stdio.h>
#include <rpc.h>
#include <string.h>
#include <stdio.h>
#include "client.h"
#include "server.h"
#include <pthread.h>

void heartbeat(SOCKET sock);
void listen_heartbeat(SOCKET sock);
SOCKET heartbeat_init();

typedef struct {
    uuid_t uuid;
    SOCKET sock;
    pthread_t thread;
} Client;

void* heartbeat_accept_thread(void* args);
void* heartbeat_listen_thread(void* args);
#endif //HEARTBEAT_HEARTBEAT_H