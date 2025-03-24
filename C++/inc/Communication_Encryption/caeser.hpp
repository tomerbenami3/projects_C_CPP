#ifndef PALANTIR_CAESER_H
#define PALANTIR_CAESER_H

#include "abstract_encode.hpp"
#include "message.hpp"
#include <string>
#include <unistd.h>


namespace palantir {


class Caeser : public AbstractEncoder {

public:
    explicit Caeser(int shift = 0);
    virtual ~Caeser() override = default;
    
    char encode(char ch) override;

private:
    int m_shift;
};


}

#endif // PALANTIR_CAESER_H