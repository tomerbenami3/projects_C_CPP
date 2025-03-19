#include "var_node.hpp"
#include <string>

namespace ast {


VarNode::VarNode(const std::string& varName)
: name(varName)
{}

double VarNode::evaluate(std::map<std::string, double>& context) const
{
    if (context.find(name) == context.end()) {
        throw std::runtime_error("Variable '" + name + "' not found in context.");
    }
    return context.at(name);
}

std::string VarNode::toPostfix() const
{
    return name;
}

std::string VarNode::toInfix() const
{
    return name;
}

}

