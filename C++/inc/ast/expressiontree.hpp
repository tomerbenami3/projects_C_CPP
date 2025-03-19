#ifndef AST_EXPRESSION_TREE_H
#define AST_EXPRESSION_TREE_H

#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <stdexcept>
#include "abstract_node.hpp"
#include "value_node.hpp"
#include "var_node.hpp"
#include "op_node.hpp"

namespace ast {
    class ExpressionTree {
    private:
        std::unique_ptr<Node> root;

    public:
        ExpressionTree() : root(nullptr) {}

        void buildFromPostfix(const std::vector<std::string>& postfix) {
            std::stack<std::unique_ptr<Node>> stack;

            for (const auto& token : postfix) {
                if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                    stack.push(std::make_unique<ValueNode>(std::stod(token)));
                } else if (std::isalpha(token[0])) {
                    stack.push(std::make_unique<VarNode>(token));
                } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                    if (stack.size() < 2) {
                        throw std::runtime_error("Invalid postfix expression: not enough operands.");
                    }

                    auto right = std::move(stack.top());
                    stack.pop();
                    auto left = std::move(stack.top());
                    stack.pop();

                    stack.push(std::make_unique<OpNode>(token[0], std::move(left), std::move(right)));
                } else {
                    throw std::runtime_error("Invalid token in postfix expression: " + token);
                }
            }

            if (stack.size() != 1) {
                throw std::runtime_error("Invalid postfix expression: too many operands.");
            }
            root = std::move(stack.top());
            stack.pop();
        }

        double compute(const std::map<std::string, double>& context) const {
            if (!root) {
                throw std::runtime_error("Expression tree is empty.");
            }
            return root->evaluate(context);
        }

        std::string toPostfix() const {
            if (!root) {
                throw std::runtime_error("Expression tree is empty.");
            }
            return root->toPostfix();
        }

        std::string toInfix() const {
            if (!root) {
                throw std::runtime_error("Expression tree is empty.");
            }
            return root->toInfix();
        }
    };
}

#endif //AST_EXPRESSION_TREE_H