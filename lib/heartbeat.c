#include "heartbeat.h"


void heartbeat(SOCKET sock) {
    client_send(sock, "BEAT", sizeof("BEAT"));
}

SOCKET heartbeat_init() {
    SOCKET sock = server_init();
    return sock;
}

void heartbeat_accept_thread(SOCKET sock, Client *clients, uint16_t* clients_count) {

    SOCKET client = accept(sock, NULL, NULL);
    if (client == INVALID_SOCKET) {
        perror("invalid socket");
        return;
    }

    uuid_t uuid;
    int n = recv(client, (char*)&uuid, sizeof(uuid), 0);
    if (n <= 0) {
        perror("recv");
        return;
    }

    RPC_CSTR str;
    UuidToStringA(&uuid, &str);
    printf("Connected client with UUID: %s\n", str);

    clients[*clients_count].sock = client;
    clients[*clients_count].uuid = uuid;
    (*clients_count)++;

}
void hearbeat_listen_thread(Client* client) {
    int timeout_ms = 10000;
    setsockopt(client->sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout_ms, sizeof(timeout_ms));
    for (;;) {
        unsigned char buffer[1024] = {0};
        int n = recv(client->sock, buffer, sizeof(buffer), 0);
        if (n > 0) {
            printf("Received: %s", buffer);
        }
    }
}




