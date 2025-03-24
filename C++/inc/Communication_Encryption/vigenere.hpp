#ifndef PALANTIR_VIGENERE_ENC_HPP
#define PALANTIR_VIGENERE_ENC_HPP
#include "abstract_encode.hpp"

namespace palantir {

class Vigenere : public AbstractEncoder {
public:
    explicit Vigenere(const std::string& key);

private:
    char encode(char ch) override;

private:
    std::string m_key;
    size_t m_index;
};

}


#endif // PALANTIR_VIGENERE_ENC_HPP
