#ifndef AST_ABSTRACT_NODE_H
#define AST_ABSTRACT_NODE_H

#include <string>
#include <map>

namespace ast {
class Node {

public:
    virtual ~Node() = default;

    virtual double evaluate(std::map<std::string, double>& context) const = 0;

    virtual std::string toPostfix() const = 0;

    virtual std::string toInfix() const = 0;
};


}

#endif //AST_ABSTRACT_NODE_H
