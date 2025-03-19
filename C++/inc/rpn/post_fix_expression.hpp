#ifndef RPN_POST_FIX_EXPRESSION_HPP
#define RPN_POST_FIX_EXPRESSION_HPP

#include "rpn/token.hpp"
#include "rpn/expression_node.hpp"
#include <memory>
#include <vector>

namespace rpn {

std::unique_ptr<ExpressionNode> parse(const std::vector<Token>& tokens);

} // namespace rpn

#endif // RPN_POST_FIX_EXPRESSION_HPP
