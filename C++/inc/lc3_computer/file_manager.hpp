#ifndef LC3_FILE_MANAGER_H
#define LC3_FILE_MANAGER_H

#include <fstream>
#include <string>

namespace lc3 {


class FileManager {

public:
    FileManager(const std::string& file_name);
    ~FileManager();

    bool read_next_instruction(int16_t& ins);

    // has_next_instruction()? bool?

private:
    std::ifstream m_file;
    
};


}


#endif // LC3_FILE_MANAGER_H
