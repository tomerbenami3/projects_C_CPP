#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <string>
#include <memory>

class TcpClient {
public:
    TcpClient(int socket, int id);
    ~TcpClient();

    void start();
    void send(const std::string& message);  // ← ADD THIS

private:
    int socket_;
    int id_;
};

#endif // TCP_CLIENT_HPP
