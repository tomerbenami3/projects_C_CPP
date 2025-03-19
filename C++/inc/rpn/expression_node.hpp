#ifndef RPN_EXPRESSION_NODE_HPP
#define RPN_EXPRESSION_NODE_HPP

#include <memory>
#include <unordered_map>
#include <string_view>
#include <variant>

namespace rpn {

class ExpressionNode {
public:
    virtual ~ExpressionNode() = default;
    virtual int evaluate(const std::unordered_map<std::string_view, int>& variables) const = 0;
};

class NumberNode : public ExpressionNode {
public:
    explicit NumberNode(int value);
    int evaluate(const std::unordered_map<std::string_view, int>& variables) const override;

private:
    int m_value;
};

class VariableNode : public ExpressionNode {
public:
    explicit VariableNode(std::string_view name);
    int evaluate(const std::unordered_map<std::string_view, int>& variables) const override;

private:
    std::string_view m_name;
};

class OperatorNode : public ExpressionNode {
public:
    OperatorNode(char op, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);
    int evaluate(const std::unordered_map<std::string_view, int>& variables) const override;

private:
    char m_op;
    std::unique_ptr<ExpressionNode> m_left, m_right;
};

}

#endif //RPN_EXPRESSION_NODE_HPP