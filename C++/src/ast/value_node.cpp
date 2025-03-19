#include "value_node.hpp"

namespace ast {

ValueNode::ValueNode(double val)
: value(val)
{

}

double ValueNode::evaluate(std::map<std::string, double>&) const
{
    return value;
}

std::string ValueNode::toPostfix() const
{
    return std::to_string(value);
}

std::string ValueNode::toInfix() const
{
    return std::to_string(value);
}


}
