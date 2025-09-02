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
    RPC_CSTR str;
    UuidToStringA(&uuid, &str);
    printf("Created UUID: %s\n", str);
    client_send(sock, (const char*)&uuid, sizeof(uuid));

    for (;;Sleep(1000)) {
        heartbeat(sock);
    }
    getchar();
    client_close(sock);



    return 0;
}