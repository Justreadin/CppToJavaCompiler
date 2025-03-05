#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "parser/ASTPrinter.h"

int main() {
    std::string code = R"(
        int x = 10;
        return x + 5;
    )";

    Lexer lexer(code);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    ASTNodePtr ast = parser.parse();

    std::cout << "Parsed AST:\n";
    ASTPrinter::print(ast);

    return 0;
}
