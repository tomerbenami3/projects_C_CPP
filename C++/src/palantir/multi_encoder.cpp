#include "multi_encoder.hpp"


namespace palantir {


MultiEncoder::MultiEncoder(std::vector<AbstractEncoder*>& encoders)
: m_encoders(encoders)
{}

char MultiEncoder::encode(char ch)
{
    for(auto current_encoder : m_encoders) {
        ch = current_encoder->encode(ch);
    }

    return ch;
}

}