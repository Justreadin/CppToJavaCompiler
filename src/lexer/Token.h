#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TokenTypes.h"

class Token {
public:
    TokenType type;
    std::string value;
    int line, column;

    Token(TokenType type, const std::string& value, int line, int column);

    std::string toString() const;
};

#endif // TOKEN_H
