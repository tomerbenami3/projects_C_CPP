#include "op_node.hpp"

namespace ast {


OpNode::OpNode(char op, std::unique_ptr<Node> leftNode, std::unique_ptr<Node> rightNode)
: operation(op),
left(std::move(leftNode)),
right(std::move(rightNode))
{}

double OpNode::evaluate(std::map<std::string, double>& context) const {
    if (!left || !right) {
        throw std::runtime_error("Invalid operation node: missing child nodes.");
    }

    double leftValue = left->evaluate(context);
    double rightValue = right->evaluate(context);

    switch (operation) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                throw std::runtime_error("Division by zero.");
            }
            return leftValue / rightValue;
        default:
            throw std::runtime_error("Unsupported operation: " + std::string(1, operation));
    }
}

std::string OpNode::toPostfix() const {
    return left->toPostfix() + " " + right->toPostfix() + " " + operation;
}

std::string OpNode::toInfix() const {
    return "(" + left->toInfix() + " " + operation + " " + right->toInfix() + ")";
}

}