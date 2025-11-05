//
// Created by awlik on 11/5/25.
//

#ifndef HEARTBEAT_PING_H
#define HEARTBEAT_PING_H

#include "../socket.h"
#include <netinet/ip_icmp.h>
#include <string.h>

int ping_host(const char* ip_address);
unsigned short checksum(void *b, int len);

#endif //HEARTBEAT_PING_H