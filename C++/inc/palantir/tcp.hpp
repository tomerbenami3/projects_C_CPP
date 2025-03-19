#ifndef PALANTIR_TCP_H
#define PALANTIR_TCP_H

#include "tcp_socket.hpp"
#include "abstract_source.hpp"
#include "abstract_dest.hpp"

#include <netinet/in.h>
#include <string>

namespace palantir
{

class TCPSource : public AbstractSource
{
public:
    TCPSource(std::string ip, size_t port);
    ~TCPSource() override = default;

    std::string read() override;

private:
    SocketTCPSource m_socket;
};



class TCPDestination : public AbstractDestination
{
public:
    TCPDestination(std::string ip, size_t port);
    ~TCPDestination() override = default;

    void write(std::string const& text) override;

private:
    SocketTCPDestination m_socket;
};

}

#endif // PALANTIR_TCP_H