#include "uart_interface.hpp"
#include <serial/serial.h>
#include <thread>
#include <atomic>
#include <iostream>

class SerialUART : public UARTInterface {
public:
    SerialUART() : stopThread(false) {}

    ~SerialUART() override {
        stopThread = true;
        if (readerThread.joinable())
            readerThread.join();
    }

    bool open(const std::string& port, unsigned long baudrate) override {
        try {
            serial.setPort(port);
            serial.setBaudrate(baudrate);
            serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
            serial.setTimeout(timeout);
            serial.open();

            if (serial.isOpen()) {
                readerThread = std::thread(&SerialUART::readLoop, this);
                return true;
            }
        } catch (const std::exception& e) {
            std::cerr << "UART open failed: " << e.what() << std::endl;
        }
        return false;
    }

    void writeLine(const std::string& line) override {
        std::string new_line = line + "\r\n";
        serial.write(new_line);
    }

    std::string readLine() override {
        return serial.readline(1024, "\r\n");
    }

    bool available() override {
        return serial.available();
    }

    void setReceiveCallback(std::function<void(const std::string&)> cb) override {
        callback = std::move(cb);
    }

    void send(const std::string& data) override {
        serial.write(data);  // This sends raw data
    }

private:
    void readLoop() {
        while (!stopThread) {
            if (serial.available()) {
                std::string line = serial.readline(1024, "\r\n");
                if (!line.empty() && callback)
                    callback(line);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }

    serial::Serial serial;
    std::function<void(const std::string&)> callback;
    std::thread readerThread;
    std::atomic<bool> stopThread;
};

// Factory function to create an instance
std::shared_ptr<UARTInterface> createUART() {
    return std::make_shared<SerialUART>();
}
