#ifndef PALANTIR_ENCODER_H
#define PALANTIR_ENCODER_H

#include "message.hpp"
#include <unistd.h>
#include <string>

namespace palantir {


class AbstractEncoder {

public:
    virtual ~AbstractEncoder() = default;

    virtual char encode(char ch) = 0;

protected:
    explicit AbstractEncoder() = default;
    AbstractEncoder(AbstractEncoder const&) = default;
    AbstractEncoder& operator=(AbstractEncoder const&) = default;

};


}

#endif // PALANTIR_ENCODER_H