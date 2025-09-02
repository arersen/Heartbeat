//
// Created by waflek on 02.09.2025.
//

#ifndef HEARTBEAT_SOCKET_H
#define HEARTBEAT_SOCKET_H

#include <stdio.h>

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
#include <stdint.h>

#endif //HEARTBEAT_SOCKET_H