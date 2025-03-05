#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "../parser/ASTNode.h"
#include "../parser/SymbolTable.h"
#include "../parser/TypeChecker.h"
#include "JavaEmitter.h"
#include "OutputWriter.h"

class CodeGenerator {
public:
    CodeGenerator(const std::string& outputFilename);
    void generate(ASTNodePtr ast);

private:
    SymbolTable symbolTable;
    JavaEmitter javaEmitter;
    OutputWriter outputWriter;
};

#endif // CODEGENERATOR_H
