#ifndef PALANTIR_ROT13_H
#define PALANTIR_ROT13_H

#include "abstract_encode.hpp"
#include "message.hpp"
#include <string>
#include <unistd.h>


namespace palantir {


class Rot13 : public AbstractEncoder {

public:
    virtual ~Rot13() override = default;

    char encode(char ch) override;
};


}

#endif // PALANTIR_ROT13_H