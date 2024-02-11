#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
enum TokenType {
    Identifier,
    Number,
    Operator,
    String,
    Newline,
    Indent,
    Dedent,
    Comment,
    Other
};
struct Token {
    std::string value;
    TokenType type;
};
std::vector<Token> tokenize(const std::string& code) {
    std::istringstream iss(code);
    std::string line;
    std::vector<Token> tokens;
    while (std::getline(iss, line)) {
        std::istringstream line_stream(line);
        std::string token;
        while (line_stream >> token) {
            bool is_number = true;
            for (char c : token) {
                if (!std::isdigit(c)) {
                    is_number = false;
                    break;
                }
            }
            if (is_number) {
                tokens.push_back({token, Number});
            }
            else if (token.front() == '"' && token.back() == '"') {
                tokens.push_back({token, String});
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "=") {
                tokens.push_back({token, Operator});
            }
            else if (token.front() == '#') {
                tokens.push_back({token, Comment});
            }
            else if (std::isalpha(token.front())) {
                tokens.push_back({token, Identifier});
            }
            else if (token == "\n") {
                tokens.push_back({token, Newline});
            }
            else {
                tokens.push_back({token, Other});
            }
        }
        tokens.push_back({"\n", Newline}); 
    }
    return tokens;
}
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case Identifier:
            return "Identifier";
        case Number:
            return "Number";
        case Operator:
            return "Operator";
        case String:
            return "String";
        case Newline:
            return "Newline";
        case Indent:
            return "Indent";
        case Dedent:
            return "Dedent";
        case Comment:
            return "Comment";
        default:
            return "Other";
    }
}
int main() {
    std::cout << "Enter C++ code (press Ctrl+D to finish):\n";
    std::string code;
    std::getline(std::cin, code);
    std::vector<Token> tokens = tokenize(code);
    for (const auto& token : tokens) {
        std::cout << std::setw(10) << std::left << token.value << " : " << tokenTypeToString(token.type) << std::endl;
    }
    return 0;
}

