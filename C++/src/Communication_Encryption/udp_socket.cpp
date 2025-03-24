#include "udp_socket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <exception>

namespace palantir {

UDPSocketSrc::UDPSocketSrc(std::string ip, size_t port)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(m_socket < 0) {
        throw std::runtime_error("Failed to open socket.\n");
    }

    sockaddr_in sin;
    std::memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_port = htons(port);

    int result = bind(m_socket, (sockaddr*)&sin, sizeof(sin));
    
    if(result != 0) {
        throw std::runtime_error("Failed to bind.\n");
    }
}

UDPSocketSrc::~UDPSocketSrc()
{
    if (m_socket > 0){
        close(m_socket);
    }
}

std::string UDPSocketSrc::receive()
{
    const size_t buffer_size = 64000;
    char* buffer = new char[buffer_size];
    std::memset(buffer, 0, buffer_size);

    ssize_t received_bytes = recvfrom(m_socket, buffer, buffer_size - 1, 0, nullptr, nullptr);
    if (received_bytes < 0)
    {
        perror("UDPSource::read: Failed to receive data");
        return "";
    }

    std::string copy(buffer, received_bytes);

    delete[] buffer;

    return copy;
}

int UDPSocketSrc::get_socket()
{
    return m_socket;
}

// ------------------ DESTINATION -------------------

UDPSocketDst::UDPSocketDst(std::string ip, size_t port)
: m_ip(ip)
, m_port(port)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(m_socket < 0) {
        throw std::runtime_error("Failed to open socket.\n");
    }

    sockaddr_in sin;
    std::memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_port = htons(port);
}

UDPSocketDst::~UDPSocketDst()
{
    if (m_socket > 0){
        close(m_socket);
    }
}

void UDPSocketDst::send(std::string const& msg)
{
    sockaddr_in sin;
    std::memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_ip.c_str()); 
    sin.sin_port = htons(m_port);

    ssize_t sent_bytes = sendto(m_socket, msg.c_str(), msg.size(), 0, 
                                reinterpret_cast<sockaddr*>(&sin), sizeof(sin));
    if (sent_bytes < 0)
    {
        perror("UDPDestination::write: Failed to send data");
    }
}

int UDPSocketDst::get_socket()
{
    return m_socket;
}


}