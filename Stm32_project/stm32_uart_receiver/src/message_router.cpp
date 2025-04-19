#include "message_router.hpp"
#include <iostream>

std::unordered_map<int, std::shared_ptr<TcpClient>> MessageRouter::clients;
std::mutex MessageRouter::mutex;
std::shared_ptr<UARTInterface> MessageRouter::uart = nullptr;

void MessageRouter::registerClient(int id, std::shared_ptr<TcpClient> client) {
    std::lock_guard<std::mutex> lock(mutex);
    clients[id] = std::move(client);
}

void MessageRouter::removeClient(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.erase(id);
}

void MessageRouter::routeToClient(int id, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = clients.find(id);
    if (it != clients.end()) {
        it->second->send(message);
    }
}

void MessageRouter::broadcast(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    for (const auto& [id, client] : clients) {
        client->send(message);
    }
}

void MessageRouter::setUART(std::shared_ptr<UARTInterface> uartInstance) {
    uart = uartInstance;
}

void MessageRouter::unregisterClient(int id) {
    removeClient(id);
}

void MessageRouter::handleClientCommand(int clientId, const std::string& command) {
    std::cout << "📥 Client " << clientId << " says: " << command << std::endl;

    if (!uart) return;

    if (command.rfind("SETCONFIG", 0) == 0) {
        uart->writeLine(command);
    }
    else if (command.rfind("GET ", 0) == 0) {
        uart->writeLine(command);
    }
    else {
        uart->writeLine(command);  // Any other command
    }

    // Send ACK to client
    if (clients.find(clientId) != clients.end()) {
        clients[clientId]->send("ACK: " + command + "\r\n");
    }
}

