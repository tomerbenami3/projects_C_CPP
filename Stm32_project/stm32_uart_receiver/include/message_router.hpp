#ifndef MESSAGE_ROUTER_HPP
#define MESSAGE_ROUTER_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include "tcp_client.hpp"
#include "uart_interface.hpp"

class MessageRouter {
public:
    static void registerClient(int id, std::shared_ptr<TcpClient> client);
    static void removeClient(int id);
    static void unregisterClient(int id);
    static void routeToClient(int id, const std::string& message);
    static void broadcast(const std::string& message);
    static void setUART(std::shared_ptr<UARTInterface> uart);
    static void handleClientCommand(int id, const std::string& command);

private:
    static std::unordered_map<int, std::shared_ptr<TcpClient>> clients;
    static std::mutex mutex;
    static std::shared_ptr<UARTInterface> uart;
};

#endif // MESSAGE_ROUTER_HPP
