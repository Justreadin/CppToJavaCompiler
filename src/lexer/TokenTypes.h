#ifndef TOKENTYPES_H
#define TOKENTYPES_H

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SEPARATOR,
    STRING_LITERAL,
    COMMENT,
    UNKNOWN,
    END_OF_FILE
};

#endif // TOKENTYPES_H
