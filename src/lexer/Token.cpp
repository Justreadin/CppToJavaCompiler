#include "Token.h"
#include <sstream>

Token::Token(TokenType type, const std::string& value, int line, int column)
    : type(type), value(value), line(line), column(column) {}

std::string Token::toString() const {
    std::ostringstream oss;
    oss << "Token(" << value << ", " << line << ":" << column << ")";
    return oss.str();
}
