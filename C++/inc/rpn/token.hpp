#ifndef RPN_TOKEN_HPP
#define RPN_TOKEN_HPP

#include <variant>
#include <string_view>
#include <string>

namespace rpn {

enum class TokenType {
    NUMBER,
    VARIABLE,
    OPERATOR
};

using TokenValue = std::variant<int, std::string_view, char>;

struct Token {
    TokenType type;
    TokenValue value;
};

inline std::string token_type_to_string(TokenType type) {
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::VARIABLE: return "VARIABLE";
        case TokenType::OPERATOR: return "OPERATOR";
        default: return "UNKNOWN";
    }
}

std::vector<Token> tokenize(std::string_view input);

} // namespace rpn

#endif // RPN_TOKEN_HPP
