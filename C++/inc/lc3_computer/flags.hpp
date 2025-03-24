#ifndef LC3_FLAGS_H
#define LC3_FLAGS_H

#include <array>
#include <cstdint>
#include <cstddef>

namespace lc3 {


class Flags {
public:
    Flags();
    ~Flags() = default;

    void update_flags(int16_t const& res);

    bool get_nflag();
    bool get_zflag();
    bool get_pflag();

private:
    std::array<bool, 3> m_flags;
    
};


}


#endif // LC3_FLAGS_H
