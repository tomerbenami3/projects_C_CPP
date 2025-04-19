#include "tcp_client.hpp"
#include <unistd.h>
#include <thread>
#include <cstring>
#include "message_router.hpp"

TcpClient::TcpClient(int socket, int id) : socket_(socket), id_(id) {}

TcpClient::~TcpClient() {
    close(socket_);
}

void TcpClient::start() {
    std::thread([this]() {
        char buffer[1024];
        while (true) {
            ssize_t bytes = read(socket_, buffer, sizeof(buffer) - 1);
            if (bytes <= 0) {
                MessageRouter::unregisterClient(id_);
                break;
            }
            buffer[bytes] = '\0';
            MessageRouter::handleClientCommand(id_, std::string(buffer));
        }
    }).detach();
}

void TcpClient::send(const std::string& message) {
    write(socket_, message.c_str(), message.length());
}
