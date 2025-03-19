#ifndef PALANTIR_MESSAGE_H
#define PALANTIR_MESSAGE_H
#include <vector>

namespace palantir {


class Message {

public:
    Message(std::string message);
    ~Message() = default;

    std::string& getmsg();

private:
    std::string m_message;
};

}

#endif // PALANTIR_MESSAGE_H