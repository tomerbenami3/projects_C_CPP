#ifndef PALANTIR_XorEnc_H
#define PALANTIR_XorEnc_H

#include "abstract_encode.hpp"
#include <string>

namespace palantir {


class XorEnc : public AbstractEncoder {

public:
    explicit XorEnc(std::string key);
    virtual ~XorEnc() override = default;

    char encode(char ch) override;
    

private:
    std::string m_key;
    size_t m_index;
};


}

#endif // PALANTIR_XorEnc_H