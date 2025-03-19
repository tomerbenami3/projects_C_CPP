#ifndef AST_VAR_NODE_H
#define AST_VAR_NODE_H

#include <string>
#include <map>
#include "abstract_node.hpp"

namespace ast {
class VarNode : public Node {

public:
    explicit VarNode(const std::string& varName);

    double evaluate(std::map<std::string, double>& context) const override;
    std::string toPostfix() const override;
    std::string toInfix() const override;

private:
    std::string name;
    };
}

#endif //AST_VAR_NODE_H