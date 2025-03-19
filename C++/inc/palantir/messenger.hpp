#ifndef PALANTIR_MESSENGER_H
#define PALANTIR_MESSENGER_H

#include <string>
#include "abstract_source.hpp"
#include "abstract_dest.hpp"
#include "abstract_encode.hpp"

namespace palantir {


class Messenger {

public:
    Messenger(AbstractSource& src, AbstractDestination& dst, AbstractEncoder& enc);
    ~Messenger() = default;

    void execute();

private:
    AbstractSource& m_src;
    AbstractDestination& m_dst;
    AbstractEncoder& m_enc;
};


}

#endif // PALANTIR_MESSENGER_H