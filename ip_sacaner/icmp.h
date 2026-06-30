#ifndef ICMP_H
#define ICMP_H

#include <cstdint>
#include <netinet/in.h>

#define ICMP_ECHO_REPLY   0
#define ICMP_ECHO_REQUEST 8
#define ICMP_PAYLOAD_SIZE 56

struct IcmpEchoHeader {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
};

uint16_t icmp_checksum(const void *data, size_t len);

class IcmpPing {
public:
    IcmpPing();
    ~IcmpPing();

    bool open();
    bool ping(const char *ip, int timeout_ms);
    void close();

private:
    int sockfd_;
    uint16_t icmp_id_;
    uint16_t seq_;

    bool sendEcho(const struct sockaddr_in &addr);
    bool recvReply(int timeout_ms);
};

#endif // ICMP_H
