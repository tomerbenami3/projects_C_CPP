#ifndef PALANTIR_NULLENC_H
#define PALANTIR_NULLENC_H

#include "abstract_encode.hpp"
#include "message.hpp"
#include <string>
#include <unistd.h>


namespace palantir {


class NullEnc : public AbstractEncoder {

public:
    ~NullEnc() override = default;
    
    char encode(char ch) override;
};


}

#endif // PALANTIR_NULLENC_H