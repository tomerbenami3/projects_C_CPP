#include "file_manager.hpp"
#include <stdexcept>


namespace lc3
{

FileManager::FileManager(const std::string& file_name)
: m_file(file_name, std::ios::binary)
{
    if(!m_file.is_open()) {
        throw std::runtime_error("failed to open file\n");
    }
}

FileManager::~FileManager()
{
    if(!m_file.is_open()) {
        m_file.close();
    }
}

bool FileManager::read_next_instruction(int16_t& ins)
{
    uint16_t instruction = 0;
    if(m_file.read(reinterpret_cast<char*>(&instruction), sizeof(instruction))) {
        ins = static_cast<int16_t>(instruction);
        return true;
    }
    return false;
}



}