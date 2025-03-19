#include "file_writer.hpp"
#include <fstream>
#include <string>

namespace palantir {

FileDestination::FileDestination(const std::string file_name)
: m_file_name(file_name, std::ios::out)
{
    if(!m_file_name.is_open()) {
        throw std::runtime_error("failed to open file\n");
    }
}

FileDestination::~FileDestination()
{
    if(!m_file_name.is_open()) {
        m_file_name.close();
    }
}
    
void FileDestination::write(std::string const& msg)
{
    m_file_name << msg << "\n";
}

};