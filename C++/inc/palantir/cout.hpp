#ifndef PALANTIR_COUT_H
#define PALANTIR_COUT_H

#include "abstract_dest.hpp"
#include <iostream>
#include <string>

namespace palantir {


class Cout : public AbstractDestination {

public:
    Cout();
    ~Cout() override = default;
    
    void write(std::string const& msg) override;

private:
    std::ostream& m_ostream;
    std::string m_message;
};


}

#endif // PALANTIR_COUT_H