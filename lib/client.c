//
// Created by waflek on 02.09.2025.
//

#include "client.h"

SOCKET client_init() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

#ifdef _WIN32
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
#else
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }
#endif

    return sock;
}

int client_connect(SOCKET sock) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(10001);

#ifdef _WIN32
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
#else
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
#endif
#ifdef _WIN32
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connect failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
#else
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        return -1;
    }
#endif
    //send(sock, "Hello World", strlen("Hello World"), 0);
    return 0;
}

void client_close(SOCKET sock) {
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

void client_send(SOCKET sock, const char* data, uint16_t size) {
    send(sock, data, size, 0);
}
void client_receive(SOCKET sock) {
    char buf[1024];
#ifdef _WIN32
    int n = recv(sock, buf, sizeof(buf)-1, 0);
#else
    int n = recv(sock, buf, sizeof(buf)-1, 0);
#endif
    if (n > 0) {
        buf[n] = '\0';
        printf("Received from server: %s\n", buf);
    }
}