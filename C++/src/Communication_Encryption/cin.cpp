#include "cin.hpp"
#include <iostream>

namespace palantir {

Cin::Cin()
: m_istream(std::cin)
{
}

std::string Cin::read()
{
    std::string message;
    std::cout << "Enter a message: " << "\n";
    std::getline(m_istream, message);

    return message;
}

}