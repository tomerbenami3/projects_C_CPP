#include "caeser.hpp"
#include <string>

namespace palantir {

Caeser::Caeser(int shift)
: m_shift(shift % 26)
{}

char Caeser::encode(char ch) {
        if((ch >= 'a') && (ch <= 'z')) {
            ch = (ch - 'a' + m_shift);
            if(ch < 0) {
                ch += 26 + 'a';
            } else {
                ch = ch % 26 + 'a';
            }
        } else if(ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + m_shift);
            if(ch < 0) {
                ch += 26 + 'A';
            } else {
                ch = ch % 26 + 'A';
            }
    }
    return ch;
}


}