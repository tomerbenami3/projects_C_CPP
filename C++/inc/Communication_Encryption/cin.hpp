#ifndef PALANTIR_CIN_H
#define PALANTIR_CIN_H

#include "abstract_source.hpp"
#include <iostream>
#include <string>

namespace palantir {


class Cin : public AbstractSource {

public:
    Cin();
    ~Cin() override = default;
    
    std::string read() override;

private:
    std::istream& m_istream;
    std::string m_message;
};


}

#endif // PALANTIR_CIN_H