//
// Created by waflek on 01.09.2025.
//

#include "heartbeat.h"

void test() {
    printf("Hello World\n");
}

#ifdef _WIN32
SOCKET
#else
int
#endif
server_init() {

#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKET sockfd;
#else
    int sockfd;
#endif


#ifdef _WIN32
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
#else
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
#endif

#ifdef _WIN32
    if (sockfd == INVALID_SOCKET) {
        perror("socket");
        return 1;
    }
#else
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
#endif
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10001);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    listen(sockfd, 0x7fffffff);
    return sockfd;
}

#ifdef _WIN32
void close_server(SOCKET sock)
#else
void close_server(int socket)
#endif
{
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
}

#ifdef _WIN32
void server_poll(SOCKET sock)
#else
void server_poll(int sock)
#endif
{

    SOCKET client = accept(sock, NULL, NULL);
    if(client == INVALID_SOCKET) {
        printf("accept error\n"); return;
    }

    char buf[1024];
    int n = recv(client, buf, sizeof(buf)-1, 0);
    if(n > 0) {
        buf[n] = '\0';
        printf("Received: %s\n", buf);
        send(client, "Connected!", 18, 0);
    }

    closesocket(client);
}


