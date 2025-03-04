#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_set>
#include "Token.h"

class Lexer {
private:
    std::string source;
    size_t position;
    int line, column;

    char peek() const;
    char advance();
    void skipWhitespace();

    Token identifierOrKeyword();
    Token number();
    Token stringLiteral();
    Token handleOperator();
    Token handleComment();
    Token handleSeparator();  // Added missing declaration
    Token nextToken();

    static const std::unordered_set<std::string> keywords;

public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif // LEXER_H
