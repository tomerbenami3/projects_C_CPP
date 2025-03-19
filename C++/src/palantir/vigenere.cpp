#include "vigenere.hpp"
#include <string>
#include <algorithm>

namespace palantir {

Vigenere::Vigenere(const std::string& key)
: m_key(key)
, m_index(0)
{}

char Vigenere::encode(char ch)
{
    if(isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        ch = base + (ch - base + m_key[m_index++] - 'a') % 26;
    }
    m_index %= m_key.length();
    return ch;
}


}
