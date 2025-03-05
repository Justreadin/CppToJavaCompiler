#include "Parser.h"
#include <iostream>
#include <stdexcept>

// Constructor
Parser::Parser(std::vector<Token> tokens) : tokens(tokens), currentTokenIndex(0) {}

Token Parser::peek() {
    return currentTokenIndex < tokens.size() ? tokens[currentTokenIndex] : Token(TokenType::END_OF_FILE, "EOF", 0, 0);
}

Token Parser::advance() {
    return currentTokenIndex < tokens.size() ? tokens[currentTokenIndex++] : Token(TokenType::END_OF_FILE, "EOF", 0, 0);
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

void Parser::expect(TokenType type, const std::string& errorMessage) {
    if (!match(type)) {
        throw std::runtime_error("Parsing Error: " + errorMessage + " at line " + std::to_string(peek().line));
    }
}

// ===============================
// 🛠️ Expression Parsing
// ===============================

ASTNodePtr Parser::parseExpression() {
    return parseBinaryExpression();
}

ASTNodePtr Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<NumberNode>(std::stod(tokens[currentTokenIndex - 1].value));
    }
    if (match(TokenType::STRING)) {
        return std::make_shared<StringNode>(tokens[currentTokenIndex - 1].value);
    }
    if (match(TokenType::IDENTIFIER)) {
        return std::make_shared<IdentifierNode>(tokens[currentTokenIndex - 1].value);
    }

    throw std::runtime_error("Parsing Error: Expected primary expression at line " + std::to_string(peek().line));
}

ASTNodePtr Parser::parseBinaryExpression(int precedence) {
    ASTNodePtr left = parsePrimary();

    while (match(TokenType::OPERATOR)) {
        std::string op = tokens[currentTokenIndex - 1].value;
        ASTNodePtr right = parsePrimary();
        left = std::make_shared<BinaryExpressionNode>(left, op, right);
    }

    return left;
}

// ===============================
// 🛠️ Statement Parsing
// ===============================

ASTNodePtr Parser::parseStatement() {
    if (match(TokenType::KEYWORD)) {
        std::string keyword = tokens[currentTokenIndex - 1].value;
        if (keyword == "return") {
            return parseReturnStatement();
        }
        if (keyword == "if") {
            return parseIfStatement();
        }
        if (keyword == "while") {
            return parseWhileLoop();
        }
        if (keyword == "int" || keyword == "string") {
            return parseVariableDeclaration(keyword);
        }
    }

    if (peek().type == TokenType::IDENTIFIER) {
        return parseExpression();
    }

    throw std::runtime_error("Parsing Error: Unexpected statement at line " + std::to_string(peek().line));
}

ASTNodePtr Parser::parseBlock() {
    expect(TokenType::SEPARATOR, "Expected '{' before block body");

    std::vector<ASTNodePtr> statements;
    while (peek().type != TokenType::SEPARATOR || peek().value != "}") {
        statements.push_back(parseStatement());
    }

    expect(TokenType::SEPARATOR, "Expected '}' at the end of block");
    return std::make_shared<BlockNode>(statements);
}

// ===============================
// 🛠️ Function & Variable Parsing
// ===============================

ASTNodePtr Parser::parseFunctionDeclaration() {
    std::string returnType = tokens[currentTokenIndex - 1].value;
    expect(TokenType::IDENTIFIER, "Expected function name");
    std::shared_ptr<ASTNode> functionName = std::make_shared<IdentifierNode>(tokens[currentTokenIndex - 1].value);

    expect(TokenType::SEPARATOR, "Expected '(' after function name");

    std::vector<ASTNodePtr> parameters;
    while (!match(TokenType::SEPARATOR) || tokens[currentTokenIndex - 1].value != ")") {
        parameters.push_back(parsePrimary());
        if (!match(TokenType::SEPARATOR) || tokens[currentTokenIndex - 1].value != ",") {
            break;
        }
    }

    ASTNodePtr body = parseBlock();
    return std::make_shared<FunctionDeclarationNode>(returnType, functionName, parameters, body);
}

ASTNodePtr Parser::parseVariableDeclaration(const std::string& type) {
    expect(TokenType::IDENTIFIER, "Expected variable name");
    std::shared_ptr<ASTNode> identifier = std::make_shared<IdentifierNode>(tokens[currentTokenIndex - 1].value);

    expect(TokenType::OPERATOR, "Expected '=' after variable name");
    ASTNodePtr initializer = parseExpression();

    expect(TokenType::SEPARATOR, "Expected ';' after variable declaration");
    return std::make_shared<VariableDeclarationNode>(type, identifier, initializer);
}

// ===============================
// 🛠️ Control Flow Parsing
// ===============================

ASTNodePtr Parser::parseIfStatement() {
    expect(TokenType::SEPARATOR, "Expected '(' after 'if'");
    ASTNodePtr condition = parseExpression();
    expect(TokenType::SEPARATOR, "Expected ')' after condition");

    ASTNodePtr thenBlock = parseBlock();
    ASTNodePtr elseBlock = nullptr;

    if (match(TokenType::KEYWORD) && tokens[currentTokenIndex - 1].value == "else") {
        elseBlock = parseBlock();
    }

    return std::make_shared<IfStatementNode>(condition, thenBlock, elseBlock);
}

ASTNodePtr Parser::parseWhileLoop() {
    expect(TokenType::SEPARATOR, "Expected '(' after 'while'");
    ASTNodePtr condition = parseExpression();
    expect(TokenType::SEPARATOR, "Expected ')' after condition");

    return std::make_shared<WhileLoopNode>(condition, parseBlock());
}

ASTNodePtr Parser::parseReturnStatement() {
    ASTNodePtr expr = parseExpression();
    expect(TokenType::SEPARATOR, "Expected ';' after return statement");

    return std::make_shared<ReturnStatementNode>(expr);
}

// ===============================
// 🛠️ Program Parsing
// ===============================

ASTNodePtr Parser::parseProgram() {
    std::vector<ASTNodePtr> statements;
    while (peek().type != TokenType::END_OF_FILE) {
        statements.push_back(parseStatement());
    }
    return std::make_shared<BlockNode>(statements);
}

ASTNodePtr Parser::parse() {
    return parseProgram();
}
