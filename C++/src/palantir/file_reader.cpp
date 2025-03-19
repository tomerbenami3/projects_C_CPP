#include "file_reader.hpp"
#include <fstream>

namespace palantir {

FileSource::FileSource(const std::string file_name)
: m_file_name(file_name, std::ios::in)
{
    if(!m_file_name.is_open()) {
        throw std::runtime_error("failed to open file\n");
    }
}

FileSource::~FileSource()
{
    if(!m_file_name.is_open()) {
        m_file_name.close();
    }
}
    
std::string FileSource::read()
{
    std::string line;
    if(std::getline(m_file_name, line)) {
        return line;
    } else {
        return "";
    }
}

};