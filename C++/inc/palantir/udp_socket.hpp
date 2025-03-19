#ifndef PALANTIR_UDP_SOCKET_SOURCE_H
#define PALANTIR_UDP_SOCKET_SOURCE_H

#include <string>
#include <unistd.h>


namespace palantir {


class UDPSocketSrc {

public:
    UDPSocketSrc(std::string ip, size_t port);
    virtual ~UDPSocketSrc();

    std::string receive();
    int get_socket();

private:
    int m_socket;
};

class UDPSocketDst {

public:
    UDPSocketDst(std::string ip, size_t port);
    virtual ~UDPSocketDst();

    void send(std::string const& msg);

    int get_socket();

private:
    int m_socket;
    std::string m_ip;
    size_t m_port;
};


}

#endif // PALANTIR_UDP_SOCKET_SOURCE_H