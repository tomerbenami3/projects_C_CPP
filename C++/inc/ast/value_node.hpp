#ifndef AST_VALUE_NODE_H
#define AST_VALUE_NODE_H

#include <string>
#include <map>
#include "abstract_node.hpp"

namespace ast {

class ValueNode : public Node
{
public:
    explicit ValueNode(double val);

    double evaluate(std::map<std::string, double>&) const override;

    std::string toPostfix() const override;

    std::string toInfix() const override;

private:
    double value;
};

}

#endif //AST_VALUE_NODE_H
