#include <iostream>
#include <output.hpp>

namespace bf {


Output::Output(std::ostream& os)
: m_os(os)
{}

void Output::print(char ch)
{
    m_os << ch;
}

}