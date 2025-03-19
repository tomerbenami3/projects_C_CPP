#include "tcp_socket.hpp"


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <unistd.h>



namespace palantir
{

SocketTCPSource::SocketTCPSource(std::string ip, size_t port)
{
     m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0){
        throw std::runtime_error("Unable to open TCP socket\n");
    }

    int optval = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    sockaddr_in sin;
    std::memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_port = htons(port);

    int result = bind(m_socket, (sockaddr*)&sin, sizeof(sin));
    if (result != 0){
        throw std::runtime_error("Unable to bind TCP socket\n");
    }

    result = listen(m_socket, 1);
    if (result != 0){
        throw std::runtime_error("Unable to listen TCP socket\n");
    }

    socklen_t sinLen = sizeof(sin);
    m_clientSocket = accept(m_socket, (sockaddr*)&sin, &sinLen);
    if (m_clientSocket <= 0){
        throw std::runtime_error("Unable to accept client socket to TCP socket\n");
    }
}


SocketTCPSource::~SocketTCPSource()
{
    if (m_clientSocket > 0)
    {
        close(m_clientSocket);
    }
    if (m_socket > 0)
    {
        close(m_socket);
    }
}

std::string SocketTCPSource::receive()
{
    char buffer[64000] = {0};
    ssize_t bytesRead = recv(m_clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead < 0)
    {
        throw std::runtime_error("TCPSource::read: Failed to read data");
    }

    return std::string(buffer, bytesRead);
}


//-------------------------------------------------------SOCKET TCP DESTINATION ------------------------------------------------------


SocketTCPDestination::SocketTCPDestination(std::string ip, size_t port)
: m_ip(ip)
, m_port(port)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0){
        throw std::runtime_error("Unable to open TCP socket\n");
    }

    sockaddr_in sin;
    std::memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_port = htons(m_port);

    int result = connect(m_socket, (sockaddr*)&sin, sizeof(sin));
    if (result != 0){
        throw std::runtime_error("Unable to connect TCP socket\n");
    }
}


SocketTCPDestination::~SocketTCPDestination()
{
    if (m_socket > 0){
        close(m_socket);
    }
}

void SocketTCPDestination::send(std::string const& text)
{
    ssize_t sentBytes = ::send(m_socket, text.c_str(), text.size(), 0);

    if (sentBytes < 0)
    {
        throw std::runtime_error("TCPDestination::write: Failed to send data");
    }
}


}