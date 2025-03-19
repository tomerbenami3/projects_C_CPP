#ifndef PALANTIR_ABSTRACT_SOURCE_H
#define PALANTIR_ABSTRACT_SOURCE_H

#include <string>
#include <iostream>

namespace palantir {

class AbstractSource {
public:
    virtual ~AbstractSource() = default;

    virtual std::string read() = 0;

};

}

#endif // PALANTIR_ABSTRACT_SOURCE_H