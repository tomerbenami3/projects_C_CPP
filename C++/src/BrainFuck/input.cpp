#include "input.hpp"
#include <iostream>

namespace bf {

Input::Input(std::istream& istream)
: m_istream(istream)
{
}

char Input::read_char()
{
    char ch;
    m_istream >> ch;
    return ch;
}
/*
bool Input::validate_brackets()
{
    double counter = 0;

    for(size_t index = 0; m_buffer[index] != '\0'; ++index) {
        if(counter < 0) {
            break;
        }
        if(m_buffer[index] == '[') {
            ++counter;
        } else if(m_buffer[index] == ']') {
            --counter;
        }
    }

    return counter == 0;
}

size_t Input::get_jump_address()
{
    size_t temp = m_pos;

    while(m_buffer[temp] != ']') {
        ++temp;
    }

    return temp+1;
}



size_t Input::size()
{
    return m_buffer.size();
}

size_t Input::get_position()
{
    return m_pos;
}

void Input::set_position(size_t position)
{
    m_pos = position;
}

*/


}