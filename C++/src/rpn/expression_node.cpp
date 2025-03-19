#include "rpn/expression_node.hpp"
#include <stdexcept>

namespace rpn {

// number node implementation
NumberNode::NumberNode(int value)
: m_value(value) 
{}

int NumberNode::evaluate(const std::unordered_map<std::string_view, int>&) const
{
    return m_value;
}

// variable node implementation
VariableNode::VariableNode(std::string_view name) : m_name(name) {}

int VariableNode::evaluate(const std::unordered_map<std::string_view, int>& variables) const {
    auto it = variables.find(m_name);
    if (it == variables.end()) {
        throw std::runtime_error("Variable not found: " + std::string(m_name));
    }
    return it->second;
}

// operator node implementation
OperatorNode::OperatorNode(char op, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right)
: m_op(op)
, m_left(std::move(left))
, m_right(std::move(right))
{}

int OperatorNode::evaluate(const std::unordered_map<std::string_view, int>& variables) const
{
    int leftVal = m_left->evaluate(variables);
    int rightVal = m_right->evaluate(variables);
    
    switch (m_op) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': 
            if (rightVal == 0) throw std::runtime_error("Division by zero");
            return leftVal / rightVal;
    }
    
    throw std::runtime_error("Unknown operator");
}

} // namespace rpn
