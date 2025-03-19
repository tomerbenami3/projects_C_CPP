#include "messenger.hpp"
#include "message.hpp"

namespace palantir
{

Messenger::Messenger(AbstractSource& src, AbstractDestination& dst, AbstractEncoder& enc)
: m_src(src)
, m_dst(dst)
, m_enc(enc)
{}

void Messenger::execute()
{   
    Message message(m_src.read());

    while (!message.getmsg().empty()) { 

        std::transform(message.getmsg().begin(),message.getmsg().end(),message.getmsg().begin(), [this](char ch) { return this->m_enc.encode(ch); });

        m_dst.write(message.getmsg());
        message = Message(m_src.read());
}

}
}