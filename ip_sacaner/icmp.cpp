#include "icmp.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

uint16_t icmp_checksum(const void *data, size_t len)
{
    const uint16_t *buf = static_cast<const uint16_t *>(data);
    uint32_t sum = 0;

    for (size_t i = 0; i < len / 2; i++) {
        sum += buf[i];
    }

    if (len & 1) {
        sum += static_cast<const uint8_t *>(data)[len - 1];
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return static_cast<uint16_t>(~sum);
}

IcmpPing::IcmpPing()
    : sockfd_(-1), icmp_id_(0), seq_(0)
{
}

IcmpPing::~IcmpPing()
{
    close();
}

bool IcmpPing::open()
{
    sockfd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);

    if (sockfd_ < 0) {
        sockfd_ = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (sockfd_ < 0) {
            return false;
        }
        icmp_id_ = htons(static_cast<uint16_t>(getpid()));
        return true;
    }

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if (getsockname(sockfd_, reinterpret_cast<struct sockaddr *>(&addr), &len) == 0) {
        icmp_id_ = addr.sin_port;
    }

    return true;
}

bool IcmpPing::ping(const char *ip, int timeout_ms)
{
    if (sockfd_ < 0) {
        return false;
    }

    struct sockaddr_in target;
    std::memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &target.sin_addr) != 1) {
        return false;
    }

    if (!sendEcho(target)) {
        return false;
    }

    return recvReply(timeout_ms);
}

bool IcmpPing::sendEcho(const struct sockaddr_in &addr)
{
    seq_++;

    char packet[sizeof(IcmpEchoHeader) + ICMP_PAYLOAD_SIZE];
    std::memset(packet, 0, sizeof(packet));

    IcmpEchoHeader *hdr = reinterpret_cast<IcmpEchoHeader *>(packet);
    hdr->type = ICMP_ECHO_REQUEST;
    hdr->code = 0;
    hdr->id = icmp_id_;
    hdr->seq = htons(seq_);
    hdr->checksum = 0;

    for (size_t i = 0; i < ICMP_PAYLOAD_SIZE; i++) {
        packet[sizeof(IcmpEchoHeader) + i] = static_cast<char>(i & 0xFF);
    }

    hdr->checksum = icmp_checksum(packet, sizeof(packet));

    ssize_t sent = sendto(sockfd_, packet, sizeof(packet), 0,
                          reinterpret_cast<const struct sockaddr *>(&addr),
                          sizeof(addr));

    return sent == static_cast<ssize_t>(sizeof(packet));
}

bool IcmpPing::recvReply(int timeout_ms)
{
    struct timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    char buf[2048];
    struct sockaddr_in from;
    socklen_t fromlen = sizeof(from);

    ssize_t n = recvfrom(sockfd_, buf, sizeof(buf), 0,
                         reinterpret_cast<struct sockaddr *>(&from), &fromlen);

    if (n < 0) {
        return false;
    }

    {
        const IcmpEchoHeader *icmp = nullptr;

        if (static_cast<size_t>(n) >= sizeof(struct ip) + sizeof(IcmpEchoHeader)) {
            const struct ip *ip_hdr = reinterpret_cast<const struct ip *>(buf);
            if (ip_hdr->ip_p == IPPROTO_ICMP) {
                int ip_hlen = ip_hdr->ip_hl * 4;
                if (ip_hlen >= (int)sizeof(struct ip) &&
                    n >= (ssize_t)(ip_hlen + (int)sizeof(IcmpEchoHeader))) {
                    icmp = reinterpret_cast<const IcmpEchoHeader *>(buf + ip_hlen);
                }
            }
        }

        if (icmp == nullptr &&
            static_cast<size_t>(n) >= sizeof(IcmpEchoHeader)) {
            icmp = reinterpret_cast<const IcmpEchoHeader *>(buf);
        }

        if (icmp == nullptr) {
            return false;
        }

        if (icmp->type != ICMP_ECHO_REPLY) {
            return false;
        }

        if (icmp->id != icmp_id_) {
            return false;
        }

        return true;
    }
}

void IcmpPing::close()
{
    if (sockfd_ >= 0) {
        ::close(sockfd_);
        sockfd_ = -1;
    }
}
