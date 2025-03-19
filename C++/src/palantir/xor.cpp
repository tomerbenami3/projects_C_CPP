#include "xor.hpp"
#include <algorithm>
#include <string>

namespace palantir {

XorEnc::XorEnc(std::string key)
: m_key(key)
, m_index(0)
{}

char XorEnc::encode(char ch)
{
    ch ^= m_key[m_index++];
    m_index %= m_key.size();
    return ch;
}


}