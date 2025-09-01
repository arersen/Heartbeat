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
#endif //HEARTBEAT_HEARTBEAT_H