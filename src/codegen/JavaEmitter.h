#ifndef JAVAEMITTER_H
#define JAVAEMITTER_H

#include "../parser/ASTNode.h"
#include "OutputWriter.h"

class JavaEmitter {
public:
    explicit JavaEmitter(OutputWriter& writer);

    void emitVariableDeclaration(const ASTNodePtr& node);
    void emitFunction(const ASTNodePtr& node);
    void emitReturn(const ASTNodePtr& node);
    void emitBinaryExpression(const ASTNodePtr& node);
    void emitExpression(const ASTNodePtr& node);
    void emitIfStatement(const ASTNodePtr& node);
    void emitWhileLoop(const ASTNodePtr& node);

private:
    void emitFunctionCall(const ASTNodePtr& node);
    void emitBlock(const ASTNodePtr& node);

    OutputWriter& writer;
};

#endif // JAVAEMITTER_H
