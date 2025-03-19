#ifndef LC3_MEMORY_H
#define LC3_MEMORY_H

#include <vector>
#include <cstdint>
#include <cstddef>

namespace lc3 {

const size_t default_size = 65536;

class Memory {

public:
    Memory(size_t size = default_size);
    ~Memory();

    int16_t read(int16_t address) const;
    void write(int16_t address, int16_t value);

private:
    std::vector<int16_t> m_memory;
    
};


}


#endif // LC3_MEMORY_H
