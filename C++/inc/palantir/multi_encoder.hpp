#ifndef PALANTIR_MULTI_ENCODER_H
#define PALANTIR_MULTI_ENCODER_H

#include "abstract_encode.hpp"
#include <vector>

namespace palantir {


class MultiEncoder : public AbstractEncoder {

public:
    MultiEncoder(std::vector<AbstractEncoder*>& encoders);
    ~MultiEncoder() = default;

private:
    char encode(char ch);

private:
    std::vector<AbstractEncoder*> m_encoders;
};


}

#endif // PALANTIR_MULTI_ENCODER_H