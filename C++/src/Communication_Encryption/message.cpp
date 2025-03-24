#include "message.hpp"



namespace palantir
{
Message::Message(std::string message)
: m_message(message)
{}

std::string& Message::getmsg()
{
    return m_message;
}

}