#include "rot13.hpp"
#include <algorithm>
#include <string>

namespace palantir {

char Rot13::encode(char ch)
{
        if((ch >= 'a') && (ch <= 'z')) {
            ch = (ch - 'a' + 13) % 26 + 'a';
        } else if(ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + 13) % 26 + 'A';
        }

    return ch;
}

// void Rot13::encode(Message& msg)
// {
//     std::transform(msg.getmsg().begin(),msg.getmsg().end(),msg.getmsg().begin(), [this](char ch) { return this->encode_char(ch); });
// }


}