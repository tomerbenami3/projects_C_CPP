#ifndef PALANTIR_FILE_WRITE_TO_H
#define PALANTIR_FILE_WRITE_TO_H

#include "abstract_dest.hpp"
#include <fstream>
#include <string>

namespace palantir {


class FileDestination : public AbstractDestination {

public:
    FileDestination(const std::string file_name);
    ~FileDestination() override;
    
    void write(std::string const& msg) override;

private:
    std::ofstream m_file_name;
};


}

#endif // PALANTIR_FILE_WRITE_TO_H