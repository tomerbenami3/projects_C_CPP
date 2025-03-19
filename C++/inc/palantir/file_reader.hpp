#ifndef PALANTIR_FILE_READ_FROM_H
#define PALANTIR_FILE_READ_FROM_H

#include "abstract_source.hpp"
#include <fstream>
#include <string>

namespace palantir {


class FileSource : public AbstractSource {

public:
    FileSource(const std::string file_name);
    ~FileSource() override;
    
    std::string read() override;

private:
    std::ifstream m_file_name;
};


}

#endif // PALANTIR_FILE_READ_FROM_H