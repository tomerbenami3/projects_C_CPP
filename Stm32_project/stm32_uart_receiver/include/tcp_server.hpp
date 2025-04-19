#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include "threadpool.h"

class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    void start(uint16_t port);
    void stop();

private:
    int server_fd;
    std::atomic<bool> running;
    std::thread accept_thread;
    std::unique_ptr<ThreadPool> threadPool;

    void acceptLoop();
    void handleClient(int client_fd, int client_id);
};

#endif // TCP_SERVER_HPP
