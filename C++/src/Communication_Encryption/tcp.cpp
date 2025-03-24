#include "tcp.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <iostream>

namespace palantir
{

//-------------------------------------------------------------- TCP SOURCE ---------------------------------------------------

TCPSource::TCPSource(std::string ip, size_t port) // server
: m_socket(ip,port)
{
}


std::string TCPSource::read()
{
    return m_socket.receive();
}


//-------------------------------------------------------------- TCP DESTINATION ---------------------------------------------------


TCPDestination::TCPDestination(std::string ip, size_t port) // client
: m_socket(ip, port)
{
}


void TCPDestination::write(std::string const& text)
{
    return m_socket.send(text);
}

}