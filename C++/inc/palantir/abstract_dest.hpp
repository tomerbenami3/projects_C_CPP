#ifndef PALANTIR_ABSTRACT_DEST_H
#define PALANTIR_ABSTRACT_DEST_H

#include "message.hpp"
#include <string>
#include <iostream>

namespace palantir {

class AbstractDestination {
public:
    virtual ~AbstractDestination() = default;

    virtual void write(std::string const& msg) = 0;

};

}

#endif // PALANTIR_ABSTRACT_DEST_H