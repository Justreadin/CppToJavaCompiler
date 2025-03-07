#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utils/FileReader.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "codegen/CodeGenerator.h"
#include "codegen/JavaEmitter.h"
#include "utils/Logger.h"
#include "codegen/OutputWriter.h" // ✅ Include OutputWriter

void printUsage() {
    std::cerr << "Usage: cpp2java <input.cpp> [-o output.java]" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = "output.java";

    for (int i = 2; i < argc; i++) {
        if (std::string(argv[i]) == "-o" && i + 1 < argc) {
            outputFile = argv[i + 1];
            i++;
        }
    }

    // Step 1: Read the source file
    std::string sourceCode = FileReader::readFileAsString(inputFile);
    if (sourceCode.empty()) {
        Logger::logError("Failed to read source file: " + inputFile);
        return 1;
    }
    Logger::logInfo("Source file read successfully.");

    // Step 2: Tokenization
    Lexer lexer(sourceCode); // Initialize Lexer with sourceCode
    std::vector<Token> tokens = lexer.tokenize();

    if (tokens.empty()) {
        Logger::logError("Tokenization failed.");
        return 1;
    }
    Logger::logInfo("Tokenization successful.");

    // Step 3: Parse tokens into an AST
    Parser parser(tokens);
    ASTNodePtr ast = parser.parse();
    if (!ast) {
        Logger::logError("Parsing failed.");
        return 1;
    }
    Logger::logInfo("Parsing successful. AST generated.");

    // Step 4: Generate Java code
    OutputWriter writer(outputFile);
    if (!writer.isOpen()) {
        Logger::logError("Failed to open output file: " + outputFile);
        return 1;
    }
    JavaEmitter emitter(writer);
    CodeGenerator codeGenerator(emitter);
    codeGenerator.generateCode(ast);
    Logger::logInfo("Java code generation completed.");

    writer.close();
    Logger::logInfo("Java code written to: " + outputFile);
    return 0;
}
