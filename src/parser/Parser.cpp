#include "Parser.h"
#include <iostream>
#include <stdexcept>
#include "../lexer/TokenTypes.h"

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
    return parseBinaryExpression(0);
}

ASTNodePtr Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<NumberNode>(std::stod(tokens[currentTokenIndex - 1].value));
    }
    if (match(TokenType::STRING_LITERAL)) {
        return std::make_shared<StringNode>(tokens[currentTokenIndex - 1].value);
    }
    if (match(TokenType::IDENTIFIER)) {
        return std::make_shared<IdentifierNode>(tokens[currentTokenIndex - 1].value);
    }

    throw std::runtime_error("Parsing Error: Expected primary expression at line " + std::to_string(peek().line));
}

ASTNodePtr Parser::parseBinaryExpression(int precedence) {
    ASTNodePtr left = parsePrimary();

    while (peek().type == TokenType::OPERATOR) {
        std::string op = advance().value;
        ASTNodePtr right = parsePrimary();
        left = std::make_shared<BinaryExpressionNode>(left, op, right);
    }
    return left;
}

// ===============================
// 🛠️ Statement Parsing
// ===============================

ASTNodePtr Parser::parseStatement() {
    Token current = peek();
    std::cout << "[DEBUG] Parsing statement: " << current.toString() << std::endl;

    // **Handle preprocessor directives like #include**
    if (current.type == TokenType::PREPROCESSOR_DIRECTIVE) {
        std::cout << "[INFO] Skipping preprocessor directive: " << current.value << std::endl;
        while (peek().type != TokenType::END_OF_FILE && peek().line == current.line) {
            advance();  // Skip everything on the preprocessor directive line
        }
        return nullptr; // Ignore and continue parsing
    }

    // **Function Declaration Handling First**
    if (match(TokenType::KEYWORD)) {
        std::string keyword = tokens[currentTokenIndex - 1].value;
        Token nextToken = peek();
        if (nextToken.type == TokenType::IDENTIFIER) {
            Token identifier = advance();
            if (peek().type == TokenType::SEPARATOR && peek().value == "(") {
                return parseFunctionDeclaration();  // Correctly parse function
            } else {
                return parseVariableDeclaration(keyword);  // Otherwise, parse as a variable
            }
        }
    }

    // **Return statement**
    if (match(TokenType::KEYWORD) && tokens[currentTokenIndex - 1].value == "return") {
        return parseReturnStatement();
    }

    throw std::runtime_error("Parsing Error: Unexpected statement at line " + std::to_string(peek().line));
}

ASTNodePtr Parser::parseBlock() {
    expect(TokenType::SEPARATOR, "Expected '{' before block body");

    std::vector<ASTNodePtr> statements;
    while (!(peek().type == TokenType::SEPARATOR && peek().value == "}")) {
        ASTNodePtr stmt = parseStatement();
        if (stmt) statements.push_back(stmt);
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
    while (!(peek().type == TokenType::SEPARATOR && peek().value == ")")) {
        parameters.push_back(parsePrimary());
        if (peek().type == TokenType::SEPARATOR && peek().value == ",") {
            advance();
        }
    }
    expect(TokenType::SEPARATOR, "Expected ')' after parameters");

    ASTNodePtr body = parseBlock();
    return std::make_shared<FunctionDeclarationNode>(returnType, functionName, parameters, body);
}

ASTNodePtr Parser::parseVariableDeclaration(const std::string& type) {
    expect(TokenType::IDENTIFIER, "Expected variable name");
    std::shared_ptr<ASTNode> identifier = std::make_shared<IdentifierNode>(tokens[currentTokenIndex - 1].value);

    if (match(TokenType::OPERATOR) && tokens[currentTokenIndex - 1].value == "=") {
        ASTNodePtr initializer = parseExpression();
        expect(TokenType::SEPARATOR, "Expected ';' after variable declaration");
        return std::make_shared<VariableDeclarationNode>(type, identifier, initializer);
    }
    throw std::runtime_error("Parsing Error: Expected '=' in variable declaration at line " + std::to_string(peek().line));
}

// ===============================
// 🛠️ Control Flow Parsing
// ===============================

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
        ASTNodePtr stmt = parseStatement();
        if (stmt) statements.push_back(stmt);
    }
    return std::make_shared<BlockNode>(statements);
}

ASTNodePtr Parser::parse() {
    return parseProgram();
}
