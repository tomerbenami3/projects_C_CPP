#ifndef LC3_REGISTER_FILE_H
#define LC3_REGISTER_FILE_H

#include <array>

namespace lc3 {


class RegisterFile {
public:
    RegisterFile();
    ~RegisterFile() = default;

    int16_t& operator[](size_t index);
    
private:
    std::array<int16_t, 8> m_registers;
};


}


#endif // LC3_REGISTER_FILE_H
