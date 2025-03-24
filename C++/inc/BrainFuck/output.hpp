#ifndef BF_OUTPUT_H
#define BF_OUTPUT_H

#include <string>
#include <iostream>

namespace bf {

class Output {
public:
    Output(std::ostream& os = std::cout);
    ~Output() = default;

    void print(char ch);

private:
    std::ostream& m_os;
};

}

#endif // BF_OUTPUT_H