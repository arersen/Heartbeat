#include "ping.h"

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int ping_host(const char* ip_address) {
    int sock;
    struct sockaddr_in dest_addr;
    struct icmphdr icmp_hdr;
    char packet[128];
    int packet_size;
    struct timeval tv_out;

    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        return 0;
    }

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip_address, &dest_addr.sin_addr) <= 0) {
        close(sock);
        return 0;
    }

    memset(&icmp_hdr, 0, sizeof(icmp_hdr));
    icmp_hdr.type = ICMP_ECHO;
    icmp_hdr.un.echo.id = getpid();
    icmp_hdr.un.echo.sequence = 1;
    icmp_hdr.checksum = checksum(&icmp_hdr, sizeof(icmp_hdr));

    memcpy(packet, &icmp_hdr, sizeof(icmp_hdr));
    packet_size = sizeof(icmp_hdr);

    if (sendto(sock, packet, packet_size, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) <= 0) {
        close(sock);
        return 0;
    }

    char recv_buf[1024];
    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);

    if (recvfrom(sock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&from_addr, &from_len) > 0) {
        close(sock);
        return 1;
    }

    close(sock);
    return 0;
}
