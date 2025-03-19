#ifndef PALANTIR_SOCKETTCP_H
#define PALANTIR_SOCKETTCP_H
#include <string>


namespace palantir
{
class SocketTCPSource
{
public:
    SocketTCPSource(std::string ip, size_t port);
    ~SocketTCPSource();

    std::string receive();



private: 
    int m_socket;
    int m_clientSocket; // Client socket
};



class SocketTCPDestination
{
public:
    SocketTCPDestination(std::string ip, size_t port);
    ~SocketTCPDestination();

    void send(std::string const& text);

private: 
    int m_socket;
    std::string m_ip;
    size_t m_port;
};

}



#endif // PALANTIR_SOCKETTCPSOURCE_H