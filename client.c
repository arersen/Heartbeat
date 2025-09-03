//
// Created by waflek on 02.09.2025.
//
#include "lib/heartbeat.h"

int main() {
    SOCKETTYPE sock = client_init();

    char buffer[128] = {0};
    printf("Connection ip: ");
    scanf("%s", buffer);
    printf("\n");

    if (client_connect(sock, buffer, 10001)) {
        perror("connect");
        return 1;
    }

    uuid_t uuid;
#ifdef _WIN32
    UuidCreate(&uuid);
    RPC_CSTR str;
    UuidToStringA(&uuid, &str);
    printf("Created UUID: %s\n", str);
#else
    uuid_generate(uuid);
#endif
    client_send(sock, (const char*)&uuid, sizeof(uuid));

    for (;;) {
        heartbeat(sock);
#ifdef _WIN32
        Sleep(1000);
#else
        usleep(100000);
#endif
    }
    getchar();
    client_close(sock);



    return 0;
}