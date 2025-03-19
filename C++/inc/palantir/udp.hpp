#ifndef PALANTIR_UDP_H
#define PALANTIR_UDP_H

#include "abstract_dest.hpp"
#include "abstract_source.hpp"
#include "udp_socket.hpp"
#include <iostream>
#include <string>

namespace palantir {


class UDPSource : public AbstractSource {

public:
    UDPSource(std::string ip, size_t port);
    ~UDPSource() override = default;
    
    std::string read() override;

private:
    UDPSocketSrc m_src_socket;
};

class UDPReceiver : public AbstractDestination {

public:
    UDPReceiver(std::string ip, size_t port);
    ~UDPReceiver() override = default;
    
    void write(std::string const& msg) override;

private:
    UDPSocketDst m_dst_socket;
};


}

#endif // PALANTIR_UDP_H