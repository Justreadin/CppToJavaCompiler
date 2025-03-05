#ifndef PARSER_H
#define PARSER_H

#include "../lexer/Lexer.h"
#include "ASTNode.h"
#include <vector>

class Parser {
private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    Token peek();
    Token advance();
    bool match(TokenType type);
    void expect(TokenType type, const std::string& errorMessage);

    ASTNodePtr parseExpression();
    ASTNodePtr parseStatement();
    ASTNodePtr parseBlock();
    ASTNodePtr parseFunctionDeclaration();
    ASTNodePtr parseVariableDeclaration();
    ASTNodePtr parseIfStatement();
    ASTNodePtr parseWhileLoop();
    ASTNodePtr parseReturnStatement();
    ASTNodePtr parseProgram();

public:
    Parser(std::vector<Token> tokens);
    ASTNodePtr parse();
};

#endif // PARSER_H
