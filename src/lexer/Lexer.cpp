#include <iostream>
#include "Lexer.h"
#include <cctype>
#include <ostream>
#include <unordered_set>

// Define a set of C++ keywords
const std::unordered_set<std::string> Lexer::keywords = {
    "int", "float", "double", "char", "void",
    "return", "if", "else", "while", "for",
    "break", "continue", "switch", "case", "default",
    "class", "public", "private", "protected", "static"
};

Lexer::Lexer(const std::string& source)
    : source(source), position(0), line(1), column(1) {}

char Lexer::peek() const {
    return position < source.size() ? source[position] : '\0';
}

char Lexer::advance() {
    char currentChar = peek();
    position++;
    column++;
    if (currentChar == '\n') {
        line++;
        column = 1;
    }
    return currentChar;
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) {
        advance();
    }
}

Token Lexer::identifierOrKeyword() {
    std::string value;
    while (isalnum(peek()) || peek() == '_') {
        value += advance();
    }

    TokenType type = keywords.count(value) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
    return Token(type, value, line, column - value.length());
}

Token Lexer::number() {
    std::string value;
    while (isdigit(peek())) {
        value += advance();
    }
    return Token(TokenType::NUMBER, value, line, column - value.length());
}

Token Lexer::stringLiteral() {
    advance(); // Skip the opening quote
    std::string value;
    while (peek() != '"' && peek() != '\0') {
        value += advance();
    }
    advance(); // Skip the closing quote
    return Token(TokenType::STRING_LITERAL, value, line, column - value.length() - 2);
}

Token Lexer::handleOperator() {
    std::string value;
    char current = peek();

    // Multi-character operators (==, !=, <=, >=, &&, ||)
    if (current == '=' || current == '!' || current == '<' || current == '>') {
        value += advance();
        if (peek() == '=') {
            value += advance();
        }
    }
    else if (current == '&' || current == '|') {
        value += advance();
        if (peek() == current) { // Handles &&, ||
            value += advance();
        }
    }
    // Arithmetic operators (+, -, *, /, %)
    else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '%') {
        value += advance();
    }
    // Single-character operators
    else {
        value += advance();
    }

    return Token(TokenType::OPERATOR, value, line, column - value.length());
}

Token Lexer::handleComment() {
    std::string value;
    if (peek() == '/') {
        advance();
        if (peek() == '/') { // Single-line comment
            while (peek() != '\n' && peek() != '\0') {
                value += advance();
            }
        }
        else if (peek() == '*') { // Multi-line comment
            advance();
            while (peek() != '\0') {
                char current = advance();
                value += current;
                if (current == '*' && peek() == '/') {
                    value += advance();
                    break;
                }
            }
        }
    }
    return Token(TokenType::COMMENT, value, line, column - value.length());
}

Token Lexer::handleSeparator() {
    char current = advance();
    return Token(TokenType::SEPARATOR, std::string(1, current), line, column - 1);
}

Token Lexer::nextToken() {
    skipWhitespace();

    if (isalpha(peek()) || peek() == '_') return identifierOrKeyword();
    if (isdigit(peek())) return number();
    if (peek() == '"') return stringLiteral();

    if (ispunct(peek())) {
        if (peek() == '/') {
            if (source[position + 1] == '/' || source[position + 1] == '*') {
                return handleComment();
            }
        }

        // Check for operators
        std::string operators = "+-*/%=&|<>!";
        if (operators.find(peek()) != std::string::npos) {
            return handleOperator();
        }

        // Check for separators (; , { } ( ) [ ])
        std::string separators = ";,{}()[]";
        if (separators.find(peek()) != std::string::npos) {
            return handleSeparator();
        }
    }

    if (peek() == '\0') return Token(TokenType::END_OF_FILE, "EOF", line, column);

    return Token(TokenType::UNKNOWN, std::string(1, advance()), line, column);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = nextToken();

    while (token.type != TokenType::END_OF_FILE) {
        // Debugging output for each token
        std::cout << token.toString() << " Type: " << static_cast<int>(token.type) << std::endl;

        tokens.push_back(token);
        token = nextToken();
    }
    return tokens;
}
