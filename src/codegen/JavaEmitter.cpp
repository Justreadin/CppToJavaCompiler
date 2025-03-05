#include "JavaEmitter.h"
#include <iostream>

JavaEmitter::JavaEmitter(OutputWriter& writer) : writer(writer) {}

void JavaEmitter::emitVariableDeclaration(const ASTNodePtr& node) {
    if (!node) return;

    auto varDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node);
    if (!varDecl) return;

    std::string type = varDecl->type;
    std::string name = std::dynamic_pointer_cast<IdentifierNode>(varDecl->identifier)->name;
    std::string value = varDecl->initializer ? varDecl->initializer->toString() : "";

    writer.write(type + " " + name + (value.empty() ? ";" : " = " + value + ";"));
}

void JavaEmitter::emitFunction(const ASTNodePtr& node) {
    if (!node) return;

    auto funcDecl = std::dynamic_pointer_cast<FunctionDeclarationNode>(node);
    if (!funcDecl) return;

    std::string returnType = funcDecl->returnType;
    std::string functionName = std::dynamic_pointer_cast<IdentifierNode>(funcDecl->functionName)->name;

    std::string params;
    for (size_t i = 0; i < funcDecl->parameters.size(); ++i) {
        auto param = std::dynamic_pointer_cast<IdentifierNode>(funcDecl->parameters[i]);
        if (param) {
            params += "int " + param->name; // Default to `int`, improve later
            if (i < funcDecl->parameters.size() - 1) params += ", ";
        }
    }

    writer.write(returnType + " " + functionName + "(" + params + ") {");

    if (funcDecl->body) emitBlock(funcDecl->body);

    writer.write("}");
}

void JavaEmitter::emitReturn(const ASTNodePtr& node) {
    if (!node) return;

    auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node);
    if (!returnStmt || !returnStmt->expression) return;

    writer.write("return " + returnStmt->expression->toString() + ";");
}

void JavaEmitter::emitBinaryExpression(const ASTNodePtr& node) {
    if (!node) return;

    auto binExpr = std::dynamic_pointer_cast<BinaryExpressionNode>(node);
    if (!binExpr) return;

    std::string left = binExpr->left->toString();
    std::string op = binExpr->op;
    std::string right = binExpr->right->toString();

    writer.write(left + " " + op + " " + right + ";");
}

void JavaEmitter::emitExpression(const ASTNodePtr& node) {
    if (!node) return;

    writer.write(node->toString() + ";");
}

void JavaEmitter::emitFunctionCall(const ASTNodePtr& node) {
    if (!node) return;

    auto funcCall = std::dynamic_pointer_cast<FunctionCallNode>(node);
    if (!funcCall) return;

    std::string funcName = std::dynamic_pointer_cast<IdentifierNode>(funcCall->functionName)->name;
    std::string args;
    for (size_t i = 0; i < funcCall->arguments.size(); ++i) {
        args += funcCall->arguments[i]->toString();
        if (i < funcCall->arguments.size() - 1) args += ", ";
    }

    writer.write(funcName + "(" + args + ");");
}

void JavaEmitter::emitIfStatement(const ASTNodePtr& node) {
    if (!node) return;

    auto ifStmt = std::dynamic_pointer_cast<IfStatementNode>(node);
    if (!ifStmt) return;

    writer.write("if (" + ifStmt->condition->toString() + ") {");
    emitBlock(ifStmt->thenBlock);
    writer.write("}");

    if (ifStmt->elseBlock) {
        writer.write("else {");
        emitBlock(ifStmt->elseBlock);
        writer.write("}");
    }
}

void JavaEmitter::emitWhileLoop(const ASTNodePtr& node) {
    if (!node) return;

    auto whileLoop = std::dynamic_pointer_cast<WhileLoopNode>(node);
    if (!whileLoop) return;

    writer.write("while (" + whileLoop->condition->toString() + ") {");
    emitBlock(whileLoop->body);
    writer.write("}");
}

void JavaEmitter::emitBlock(const ASTNodePtr& node) {
    if (!node) return;

    auto block = std::dynamic_pointer_cast<BlockNode>(node);
    if (!block) return;

    for (const auto& stmt : block->statements) {
        emitExpression(stmt);
    }
}
