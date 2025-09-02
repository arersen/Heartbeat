#include <stdio.h>
#include "lib/heartbeat.h"

int main(void) {
    uint16_t clients_count = 0;
    Client clients[100];
    SOCKET server = heartbeat_init();
    heartbeat_accept_thread(server, clients, &clients_count);
}