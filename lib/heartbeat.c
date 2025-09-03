#include "heartbeat.h"


void heartbeat(SOCKETTYPE sock){
    client_send(sock, "BEAT", sizeof("BEAT"));
}

SOCKETTYPE heartbeat_init() {
    SOCKETTYPE sock = server_init();
    return sock;
}

uint8_t check_token() {
    FILE* fp = fopen("token.txt", "r");
    if (!fp) {
        return 0;
    }
    fclose(fp);
    return 1;
}


void* heartbeat_accept_thread(void* args) {
    struct Args{
        SOCKETTYPE sock; Client *clients; uint16_t* clients_count;
    } *_args = (struct Args*)args;
    SOCKETTYPE sock = _args->sock;
    Client *clients = _args->clients;
    uint16_t* clients_count = _args->clients_count;

    for (;;) {
        SOCKETTYPE client = accept(sock, NULL, NULL);
#ifdef _WIN32
        if (client == INVALID_SOCKET) {
#else
        if (client < 0){
#endif
            perror("invalid socket");
            return NULL;
        }

        uuid_t uuid;
        int n = recv(client, (char*)&uuid, sizeof(uuid), 0);
        if (n <= 0) {
            perror("recv");
            return NULL;
        }

#ifdef _WIN32
        RPC_CSTR str;
        UuidToStringA(&uuid, &str);
#else
        char str[37];
        uuid_unparse(uuid, str);
#endif
        printf("Connected client with UUID: %s\n", str);

        if (check_token()) {
            printf("Sending telegram\n");
            char token[256] = {0};
            get_token(token);
            telegram_send_message(token, "763411878", str);
        } else {
            printf("Warning: u dont link telegram bot.\n");
        }
        clients[*clients_count].sock = client;
#ifdef _WIN32
        clients[*clients_count].uuid = uuid;
#else
        memcpy(&clients[*clients_count].uuid, &uuid, sizeof(uuid));
#endif

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
            return NULL;
        }
        (*clients_count)++;

    }

    free(args);
    return NULL;

}
void* heartbeat_listen_thread(void* args) {
#ifdef _WIN32
    Sleep(100);
#else
    usleep(1001000);
#endif
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
                if (memcmp(&client->uuid, &clients[0].uuid, sizeof(uuid_t)) == 0) {
                    reconnected++;
                }
            }
            if (reconnected < 2) {
                printf("Connection lost.\n");
                char token[256] = {0};
                get_token(token);
                telegram_send_message(token, "763411878", "Connection lost");
                return NULL;
            } else {
                printf("Reconnected from other IP.\n");
            }
        }

    }
    free(args);
    return NULL;
}




