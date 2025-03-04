#include <iostream>
#include "lexer/Lexer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: CppToJavaCompiler <source_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();

    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();

    std::cout << "public class Main {" << std::endl;
    std::cout << "    public static void main(String[] args) {" << std::endl;

    for (const auto& token : tokens) {
        std::cout << "        // " << token.getValue() << std::endl;
    }

    std::cout << "    }" << std::endl;
    std::cout << "}" << std::endl;

    return 0;
}
