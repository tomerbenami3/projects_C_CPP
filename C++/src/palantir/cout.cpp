#include "cout.hpp"


namespace palantir {

Cout::Cout()
: m_ostream(std::cout)
{}

void Cout::write(std::string const& msg)
{
    std::cout << "The received message: " << "\n";
    m_ostream << msg << "\n";
}

}