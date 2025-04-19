#ifndef UART_INTERFACE_HPP
#define UART_INTERFACE_HPP

#include <string>
#include <functional>

class UARTInterface {
public:
    virtual ~UARTInterface() = default;

    virtual bool open(const std::string& port, unsigned long baudrate) = 0;
    virtual void writeLine(const std::string& line) = 0;
    virtual std::string readLine() = 0;
    virtual bool available() = 0;
    virtual void setReceiveCallback(std::function<void(const std::string&)> callback) = 0;
    virtual void send(const std::string& data) = 0;
};

std::shared_ptr<UARTInterface> createUART();

#endif // UART_INTERFACE_HPP
