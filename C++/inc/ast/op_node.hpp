#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include "abstract_node.hpp"

namespace ast {
    class OpNode : public Node {

public:
    OpNode(char op, std::unique_ptr<Node> leftNode, std::unique_ptr<Node> rightNode);

    double evaluate(std::map<std::string, double>& context) const override;

    std::string toPostfix() const override;

    std::string toInfix() const override;

private:
    char operation;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    };
}
