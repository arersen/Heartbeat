#include <stdio.h>
#include "lib/heartbeat.h"

int main(void) {
    uint16_t clients_count = 0;
    Client clients[100];
    SOCKET server = heartbeat_init();

    struct Args{
        SOCKET sock; Client *clients; uint16_t* clients_count;
    } *args = (struct Args*)malloc(sizeof(struct Args));
    args->sock = server;
    args->clients = clients;
    args->clients_count = &clients_count;
    pthread_t thread;
    pthread_create(&thread, NULL, heartbeat_accept_thread, (void*)args);

    for (int i = 0; i < clients_count; i++) {
        pthread_join(clients[i].thread, NULL);
    }
    pthread_join(thread, NULL);


    getchar();
}