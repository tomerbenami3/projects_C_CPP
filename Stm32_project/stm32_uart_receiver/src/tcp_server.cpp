#include "tcp_server.hpp"
#include "tcp_client.hpp"
#include "message_router.hpp"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

TcpServer::TcpServer() : server_fd(-1), running(false) {
    threadPool = std::make_unique<ThreadPool>(4);
}

TcpServer::~TcpServer() {
    stop();
}

void TcpServer::start(uint16_t port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "❌ Failed to create socket\n";
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "❌ setsockopt failed\n";
        close(server_fd);
        return;
    }

    std::cout << "🔌 Binding to 0.0.0.0:" << port << "...\n";
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "❌ Bind failed\n";
        close(server_fd);
        return;
    }

    if (listen(server_fd, 5) < 0) {
        std::cerr << "❌ Listen failed\n";
        close(server_fd);
        return;
    }

    running = true;
    accept_thread = std::thread(&TcpServer::acceptLoop, this);
    std::cout << "🚀 TCP Server started and listening on port " << port << "\n";
}


void TcpServer::stop() {
    running = false;

    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }

    if (accept_thread.joinable()) {
        accept_thread.join();
    }
}

void TcpServer::acceptLoop() {
    int client_id = 1;

    while (running) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd >= 0) {
            int this_client_id = client_id++;
            threadPool->enqueue([this, client_fd, this_client_id]() {
                std::cout << "📥Client connected: ID = " << this_client_id << std::endl;
                handleClient(client_fd, this_client_id);
            });
        }
    }
}

void TcpServer::handleClient(int client_fd, int client_id) {
    auto client = std::make_shared<TcpClient>(client_fd, client_id);
    MessageRouter::registerClient(client_id, client);
    client->start();
}

//GET 2025-04-19 15:41:00 TO 2025-04-19 15:42:00