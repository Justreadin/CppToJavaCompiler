#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "../parser/ASTNode.h"
#include "../parser/SymbolTable.h"
#include "../parser/TypeChecker.h"
#include "JavaEmitter.h"
#include "OutputWriter.h"

class CodeGenerator {
public:
    explicit CodeGenerator(JavaEmitter& emitter);

    void generateCode(const ASTNodePtr& root);
    void generateStatement(const ASTNodePtr& node);
    void generateExpression(const ASTNodePtr& node);

private:
    SymbolTable symbolTable;
    JavaEmitter& emitter;
};

#endif // CODEGENERATOR_H
