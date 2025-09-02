#include "heartbeat.h"


void heartbeat(SOCKET sock){
    client_send(sock, "BEAT", sizeof("BEAT"));
}

SOCKET heartbeat_init() {
    SOCKET sock = server_init();
    return sock;
}

void* heartbeat_accept_thread(void* args) {
    struct Args{
        SOCKET sock; Client *clients; uint16_t* clients_count;
    } *_args = (struct Args*)args;
    SOCKET sock = _args->sock;
    Client *clients = _args->clients;
    uint16_t* clients_count = _args->clients_count;

    for (;;) {
        SOCKET client = accept(sock, NULL, NULL);
        if (client == INVALID_SOCKET) {
            perror("invalid socket");
            return NULL;
        }

        uuid_t uuid;
        int n = recv(client, (char*)&uuid, sizeof(uuid), 0);
        if (n <= 0) {
            perror("recv");
            return NULL;
        }

        RPC_CSTR str;
        UuidToStringA(&uuid, &str);
        printf("Connected client with UUID: %s\n", str);

        clients[*clients_count].sock = client;
        clients[*clients_count].uuid = uuid;

        struct Args {
            Client *client;
            Client *clients;
            uint16_t* clients_count;
        } *args = (struct Args*)malloc(sizeof(struct Args));

        args->client = &clients[*clients_count];
        args->clients = clients;
        args->clients_count = clients_count;


        if (pthread_create(&clients[*clients_count].thread, NULL, heartbeat_listen_thread, args) != 0) {
            perror("pthread_create");
            return;
        }
        (*clients_count)++;

    }

    free(args);
    return NULL;

}
void* heartbeat_listen_thread(void* args) {
    Sleep(100);
    const struct Args {
        Client *client;
        Client *clients;
        uint16_t* clients_count;
    } *_args = (struct Args*)args;
    Client* client = _args->client;
    Client* clients = _args->clients;
    uint16_t* clients_count = _args->clients_count;

    int timeout_ms = 10000;
    setsockopt(client->sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout_ms, sizeof(timeout_ms));

    unsigned char buffer[1024] = {0};
    for (;;) {
        int n = recv(client->sock, buffer, sizeof(buffer), 0);
        if (n > 0) {
            printf("Received: %s from: %d\n", buffer, *clients_count);
        } else {
            uint8_t reconnected = 0;
            for (int i = 0; i < *clients_count; i++) {
                if (memcmp(&client->uuid, &clients[0].uuid, sizeof(UUID)) == 0) {
                    reconnected++;
                }
            }
            if (reconnected < 2) {
                printf("Connection lost.\n");
                return NULL;
            } else {
                printf("Reconnected from other IP.\n");
            }
        }

    }
    free(args);
    return NULL;
}




