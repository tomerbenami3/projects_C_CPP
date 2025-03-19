#include "udp.hpp"
#include "message.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <exception>
#include "message.hpp"



namespace palantir
{

UDPSource::UDPSource(std::string ip, size_t port)
: m_src_socket(ip, port)
{
}

std::string UDPSource::read()
{
    return m_src_socket.receive();
}


//------------------------------------------------------- UDP DESTINATION ------------------------------------------------------

UDPReceiver::UDPReceiver(std::string ip, size_t port)
: m_dst_socket(ip, port)
{
    
}

void UDPReceiver::write(std::string const& msg)
{
    m_dst_socket.send(msg);
}

}