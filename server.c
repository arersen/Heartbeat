#include <stdio.h>
#include "heartbeat.h"

int main(void) {
#ifdef _WIN32
    SOCKET sock = server_init();
#else
    int sock = server_init();
#endif

    server_poll(sock);

    close_server(sock);
    return 0;
}