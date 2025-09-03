//
// Created by waflek on 01.09.2025.
//

#ifndef HEARTBEAT_HEARTBEAT_H
#define HEARTBEAT_HEARTBEAT_H
#include <stdio.h>

#ifdef _WIN32
#include <rpc.h>
#define SOCKETTYPE SOCKET
#else
#include <malloc.h>
#include <uuid/uuid.h>
#define SOCKETTYPE int
#endif

#include <string.h>
#include <stdio.h>
#include "client.h"
#include "server.h"
#include <pthread.h>
#include "telegram/telegram.h"
void heartbeat(SOCKETTYPE sock);
void listen_heartbeat(SOCKETTYPE sock);
SOCKETTYPE heartbeat_init();

typedef struct {
    uuid_t uuid;
    SOCKETTYPE sock;
    pthread_t thread;
} Client;

void* heartbeat_accept_thread(void* args);
void* heartbeat_listen_thread(void* args);


#endif //HEARTBEAT_HEARTBEAT_H