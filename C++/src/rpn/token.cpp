#include "token.hpp"
#include <vector>
#include <cctype>

namespace rpn {

std::vector<Token> tokenize(std::string_view input) {
    std::vector<Token> tokens;
    size_t start = 0;
    size_t length = input.size();

    while (start < length) {

        while (start < length && std::isspace(input[start])) {
            ++start;
        }

        if (start >= length) break;

        size_t end = start;
        while (end < length && !std::isspace(input[end])) {
            ++end;
        }

        //atm: start and end is the starting point and the end point of the substr
        std::string_view token_str = input.substr(start, end - start);

        //check if number
        if (std::isdigit(token_str[0]) || 
            (token_str[0] == '-' && token_str.size() > 1 && std::isdigit(token_str[1]))) {
            tokens.push_back({TokenType::NUMBER, std::stoi(std::string(token_str))});
        }
        //check if operator
        else if (token_str.size() == 1 && std::string("+-*/").find(token_str[0]) != std::string::npos) {
            tokens.push_back({TokenType::OPERATOR, token_str[0]});
        }
        //its probably a variable if not operator or number
        else {
            tokens.push_back({TokenType::VARIABLE, token_str});
        }

        start = end;
    }

    return tokens;
}

} // namespace rpn


