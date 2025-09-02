//
// Created by waflek on 02.09.2025.
//
#include "lib/heartbeat.h"

int main() {
    SOCKET sock = client_init();

    if (client_connect(sock)) {
        perror("connect");
        return 1;
    }

    uuid_t uuid;
    UuidCreate(&uuid);
    client_send(sock, (const char*)&uuid, sizeof(uuid));
    client_receive(sock);
    client_close(sock);

    getchar();

    return 0;
}