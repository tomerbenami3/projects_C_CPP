#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "tcp_server.hpp"
#include "uart_interface.hpp"
#include "message_router.hpp"

int main() {
    auto uart = createUART();

    if (!uart->open("/dev/tty.usbmodem1103", 115200)) {
        std::cerr << "Failed to open UART" << std::endl;
        return 1;
    }

    // Register UART with the message router
    MessageRouter::setUART(uart);

    // Set callback for incoming UART data
    uart->setReceiveCallback([](const std::string& line) {
        std::cout << "Received: " << line << std::endl;
        MessageRouter::broadcast(line);
    });

    // Start TCP server
    TcpServer server;
    server.start(5555);

    // Automatically send SETTIME with current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&now_c);

    std::ostringstream oss;
    oss << "SETTIME "
        << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

    uart->writeLine(oss.str());

    std::cout << "Listening for future messages...\n";
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

