#ifndef BF_MEMORY_H
#define BF_MEMORY_H

#include <vector>
#include <cstddef>

namespace bf {

class Memory {
public:
    Memory(size_t size = 100);
    ~Memory() = default;
    Memory(Memory const& other);
    Memory& operator=(Memory const& other);

    char& operator[](size_t const index);
    void extend_memory_right();
    void extend_memory_left();

    void add();
    void sub();
    void print();
    char& read();
    void write(char ch);
    void movright();
    void movleft();

    size_t size();
    char* position();

private:
    std::vector<char> m_memory;
    char* m_pos;
};

}
#endif // BF_MEMORY_H